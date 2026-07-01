#include <obs-module.h>
#include <obs-source.h>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <CommonCrypto/CommonDigest.h>

struct LowerThirdsData {
    obs_source_t *self;
    obs_source_t *browserSource;
    char *dbPath;
    char *selectedType;
    pthread_t dbPollThreadTid;
    bool dbPollThreadShouldRun;
};

std::vector<int> clientSockets;
pthread_mutex_t clientsMutex = PTHREAD_MUTEX_INITIALIZER;
std::string latestJsonState = "";
pthread_mutex_t stateMutex = PTHREAD_MUTEX_INITIALIZER;
int serverSocketFd = -1;
bool serverShouldRun = true;
pthread_t serverThreadTid;

std::string getDefaultDbPath() {
    const char *home = getenv("HOME");
    if (home) {
        return std::string(home) + "/Library/Application Support/com.aminuddinadl.sw-desk/sw_desk.db";
    }
    return "/Users/aminuddinadl/Library/Application Support/com.aminuddinadl.sw-desk/sw_desk.db";
}

std::string getWebSocketAcceptKey(const std::string &clientKey) {
    std::string guid = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    std::string combined = clientKey + guid;
    unsigned char hash[CC_SHA1_DIGEST_LENGTH];
    CC_SHA1(combined.data(), (CC_LONG)combined.size(), hash);
    static const char lookup[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string base64;
    int val = 0, valb = -6;
    for (unsigned char c : hash) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            base64.push_back(lookup[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) {
        base64.push_back(lookup[((val << 8) >> (valb + 8)) & 0x3F]);
    }
    while (base64.size() % 4) {
        base64.push_back('=');
    }
    return base64;
}

std::vector<uint8_t> makeTextFrame(const std::string &message) {
    std::vector<uint8_t> frame;
    frame.push_back(129);
    size_t len = message.size();
    if (len <= 125) {
        frame.push_back((uint8_t)len);
    } else if (len <= 65535) {
        frame.push_back(126);
        frame.push_back((uint8_t)((len >> 8) & 0xFF));
        frame.push_back((uint8_t)(len & 0xFF));
    } else {
        frame.push_back(127);
        for (int i = 7; i >= 0; --i) {
            frame.push_back((uint8_t)((len >> (i * 8)) & 0xFF));
        }
    }
    frame.insert(frame.end(), message.begin(), message.end());
    return frame;
}

void broadcastState(const std::string &message) {
    pthread_mutex_lock(&clientsMutex);
    std::vector<uint8_t> frame = makeTextFrame(message);
    auto it = clientSockets.begin();
    while (it != clientSockets.end()) {
        int fd = *it;
        ssize_t sent = send(fd, frame.data(), frame.size(), 0);
        if (sent < 0) {
            close(fd);
            it = clientSockets.erase(it);
        } else {
            ++it;
        }
    }
    pthread_mutex_unlock(&clientsMutex);
}

void *handleClientThread(void *arg) {
    int fd = (int)(intptr_t)arg;
    char buffer[4096];
    ssize_t bytesRead = recv(fd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        close(fd);
        return nullptr;
    }
    buffer[bytesRead] = '\0';
    std::string request(buffer);
    size_t keyPos = request.find("Sec-WebSocket-Key:");
    if (keyPos == std::string::npos) {
        close(fd);
        return nullptr;
    }
    size_t valStart = keyPos + 18;
    while (valStart < request.size() && (request[valStart] == ' ' || request[valStart] == '\t')) {
        valStart++;
    }
    size_t valEnd = request.find("\r\n", valStart);
    if (valEnd == std::string::npos) {
        close(fd);
        return nullptr;
    }
    std::string clientKey = request.substr(valStart, valEnd - valStart);
    std::string acceptValue = getWebSocketAcceptKey(clientKey);
    std::string response = 
        "HTTP/1.1 101 Switching Protocols\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Accept: " + acceptValue + "\r\n\r\n";
    send(fd, response.data(), response.size(), 0);
    pthread_mutex_lock(&clientsMutex);
    clientSockets.push_back(fd);
    pthread_mutex_unlock(&clientsMutex);
    pthread_mutex_lock(&stateMutex);
    std::string curState = latestJsonState;
    pthread_mutex_unlock(&stateMutex);
    if (!curState.empty()) {
        std::vector<uint8_t> frame = makeTextFrame(curState);
        send(fd, frame.data(), frame.size(), 0);
    }
    while (true) {
        char dummy[1024];
        ssize_t r = recv(fd, dummy, sizeof(dummy), 0);
        if (r <= 0) {
            break;
        }
    }
    pthread_mutex_lock(&clientsMutex);
    auto it = std::find(clientSockets.begin(), clientSockets.end(), fd);
    if (it != clientSockets.end()) {
        clientSockets.erase(it);
    }
    pthread_mutex_unlock(&clientsMutex);
    close(fd);
    return nullptr;
}

void *serverListenerThread(void *unused) {
    serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketFd < 0) {
        return nullptr;
    }
    int opt = 1;
    setsockopt(serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(4500);
    if (bind(serverSocketFd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(serverSocketFd);
        return nullptr;
    }
    if (listen(serverSocketFd, 5) < 0) {
        close(serverSocketFd);
        return nullptr;
    }
    while (serverShouldRun) {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int fd = accept(serverSocketFd, (struct sockaddr *)&clientAddr, &clientLen);
        if (fd < 0) {
            if (!serverShouldRun) {
                break;
            }
            continue;
        }
        pthread_t tid;
        pthread_create(&tid, nullptr, handleClientThread, (void *)(intptr_t)fd);
        pthread_detach(tid);
    }
    close(serverSocketFd);
    return nullptr;
}

void startWebSocketServer() {
    serverShouldRun = true;
    pthread_create(&serverThreadTid, nullptr, serverListenerThread, nullptr);
}

void stopWebSocketServer() {
    serverShouldRun = false;
    if (serverSocketFd != -1) {
        close(serverSocketFd);
        serverSocketFd = -1;
    }
    pthread_mutex_lock(&clientsMutex);
    for (int fd : clientSockets) {
        close(fd);
    }
    clientSockets.clear();
    pthread_mutex_unlock(&clientsMutex);
    pthread_join(serverThreadTid, nullptr);
}

const char *lowerThirdsGetName(void *unused) {
    return "Lower Thirds (SWM)";
}

void *dbPollThreadFunc(void *arg) {
    LowerThirdsData *context = (LowerThirdsData *)arg;
    std::string lastState = "";
    while (context->dbPollThreadShouldRun) {
        if (context->dbPath) {
            sqlite3 *db = nullptr;
            int rc = sqlite3_open(context->dbPath, &db);
            if (rc == SQLITE_OK) {
                sqlite3_stmt *stmt = nullptr;
                const char *query = "SELECT value FROM settings WHERE key = 'active_lower_third'";
                rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
                if (rc == SQLITE_OK) {
                    if (sqlite3_step(stmt) == SQLITE_ROW) {
                        const unsigned char *val = sqlite3_column_text(stmt, 0);
                        if (val) {
                            std::string currentStateStr((const char *)val);
                            if (currentStateStr != lastState) {
                                lastState = currentStateStr;
                                pthread_mutex_lock(&stateMutex);
                                latestJsonState = currentStateStr;
                                pthread_mutex_unlock(&stateMutex);
                                broadcastState(currentStateStr);
                            }
                        }
                    }
                    sqlite3_finalize(stmt);
                }
                sqlite3_close(db);
            }
        }
        usleep(500000);
    }
    return nullptr;
}

uint32_t hexToObsColor(const std::string &hex) {
    std::string h = hex;
    if (h[0] == '#') {
        h = h.substr(1);
    }
    uint32_t rgb = (uint32_t)std::strtoul(h.c_str(), nullptr, 16);
    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = rgb & 0xFF;
    return 0xFF000000 | (b << 16) | (g << 8) | r;
}

std::string obsColorToHex(uint32_t c) {
    uint8_t r = c & 0xFF;
    uint8_t g = (c >> 8) & 0xFF;
    uint8_t b = (c >> 16) & 0xFF;
    char hex[16];
    snprintf(hex, sizeof(hex), "#%02x%02x%02x", r, g, b);
    return std::string(hex);
}

bool activeServiceModifiedCallback(obs_properties_t *props, obs_property_t *p, obs_data_t *settings) {
    const char *dbPath = obs_data_get_string(settings, "database_path");
    const char *serviceId = obs_data_get_string(settings, "active_service");
    if (!dbPath || std::string(dbPath).empty()) {
        std::string defaultPath = getDefaultDbPath();
        obs_data_set_string(settings, "database_path", defaultPath.c_str());
        dbPath = obs_data_get_string(settings, "database_path");
    }
    if (!dbPath || !serviceId || std::string(serviceId).empty()) {
        return false;
    }
    sqlite3 *db = nullptr;
    if (sqlite3_open(dbPath, &db) == SQLITE_OK) {
        sqlite3_stmt *stmt = nullptr;
        const char *query = "SELECT title, subtitle, theme_color, text_color, style_type FROM resources WHERE id = ?";
        if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, serviceId, -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                const unsigned char *title = sqlite3_column_text(stmt, 0);
                const unsigned char *subtitle = sqlite3_column_text(stmt, 1);
                const unsigned char *themeColor = sqlite3_column_text(stmt, 2);
                const unsigned char *textColor = sqlite3_column_text(stmt, 3);
                const unsigned char *styleType = sqlite3_column_text(stmt, 4);
                if (title) {
                    obs_data_set_string(settings, "title", (const char *)title);
                }
                if (subtitle) {
                    obs_data_set_string(settings, "subtitle", (const char *)subtitle);
                }
                if (styleType) {
                    obs_data_set_string(settings, "animation_style", (const char *)styleType);
                }
                if (themeColor) {
                    obs_data_set_int(settings, "theme_color", hexToObsColor((const char *)themeColor));
                }
                if (textColor) {
                    obs_data_set_int(settings, "text_color", hexToObsColor((const char *)textColor));
                }
            }
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }
    return true;
}

void *lowerThirdsCreate(obs_data_t *settings, obs_source_t *source) {
    LowerThirdsData *context = (LowerThirdsData *)bzalloc(sizeof(LowerThirdsData));
    context->self = source;
    obs_data_t *browserSettings = obs_data_create();
    obs_data_set_string(browserSettings, "url", "http://localhost:1420/#/overlay");
    obs_data_set_int(browserSettings, "width", 1920);
    obs_data_set_int(browserSettings, "height", 1080);
    obs_data_set_bool(browserSettings, "is_local_file", false);
    context->browserSource = obs_source_create_private("browser_source", "Lower Thirds SWM Internal Browser", browserSettings);
    obs_data_release(browserSettings);
    context->dbPath = bstrdup(getDefaultDbPath().c_str());
    context->dbPollThreadShouldRun = true;
    pthread_create(&context->dbPollThreadTid, nullptr, dbPollThreadFunc, context);
    return context;
}

void lowerThirdsDestroy(void *data) {
    LowerThirdsData *context = (LowerThirdsData *)data;
    context->dbPollThreadShouldRun = false;
    pthread_join(context->dbPollThreadTid, nullptr);
    if (context->browserSource) {
        obs_source_release(context->browserSource);
    }
    if (context->dbPath) {
        bfree(context->dbPath);
    }
    if (context->selectedType) {
        bfree(context->selectedType);
    }
    bfree(context);
}

uint32_t lowerThirdsGetWidth(void *data) {
    return 1920;
}

uint32_t lowerThirdsGetHeight(void *data) {
    return 1080;
}

void lowerThirdsVideoRender(void *data, gs_effect_t *effect) {
    LowerThirdsData *context = (LowerThirdsData *)data;
    if (context->browserSource) {
        obs_source_video_render(context->browserSource);
    }
}

void saveToDatabase(const char *dbPath, const char *serviceId, const char *title, const char *subtitle, const char *animStyle, uint32_t themeColor, uint32_t textColor) {
    if (!dbPath || !serviceId || std::string(serviceId).empty()) {
        return;
    }
    std::string themeHex = obsColorToHex(themeColor);
    std::string textHex = obsColorToHex(textColor);
    std::string serviceIdStr = serviceId;
    std::string layoutType = "classic";
    if (serviceIdStr == "2" || serviceIdStr == "6") {
        layoutType = "social";
    } else if (serviceIdStr == "3" || serviceIdStr == "5") {
        layoutType = "banner";
    } else if (serviceIdStr == "4") {
        layoutType = "minimal";
    }
    sqlite3 *db = nullptr;
    if (sqlite3_open(dbPath, &db) == SQLITE_OK) {
        sqlite3_stmt *stmt1 = nullptr;
        const char *query1 = "UPDATE resources SET title = ?, subtitle = ?, theme_color = ?, text_color = ?, style_type = ? WHERE id = ?";
        if (sqlite3_prepare_v2(db, query1, -1, &stmt1, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt1, 1, title, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt1, 2, subtitle, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt1, 3, themeHex.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt1, 4, textHex.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt1, 5, animStyle, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt1, 6, serviceId, -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt1);
            sqlite3_finalize(stmt1);
        }
        std::string jsonPayload = "{\"id\":\"" + serviceIdStr + 
                                  "\",\"type\":\"" + layoutType + 
                                  "\",\"title\":\"" + title + 
                                  "\",\"subtitle\":\"" + subtitle + 
                                  "\",\"themeColor\":\"" + themeHex + 
                                  "\",\"textColor\":\"" + textHex + 
                                  "\",\"styleType\":\"" + animStyle + 
                                  "\",\"isActive\":true}";
        sqlite3_stmt *stmt2 = nullptr;
        const char *query2 = "INSERT INTO settings (key, value) VALUES ('active_lower_third', ?) ON CONFLICT(key) DO UPDATE SET value=excluded.value";
        if (sqlite3_prepare_v2(db, query2, -1, &stmt2, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt2, 1, jsonPayload.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt2);
            sqlite3_finalize(stmt2);
        }
        sqlite3_close(db);
    }
}

void lowerThirdsUpdate(void *data, obs_data_t *settings) {
    LowerThirdsData *context = (LowerThirdsData *)data;
    const char *dbPath = obs_data_get_string(settings, "database_path");
    const char *serviceId = obs_data_get_string(settings, "active_service");
    const char *title = obs_data_get_string(settings, "title");
    const char *subtitle = obs_data_get_string(settings, "subtitle");
    const char *animStyle = obs_data_get_string(settings, "animation_style");
    uint32_t themeColor = (uint32_t)obs_data_get_int(settings, "theme_color");
    uint32_t textColor = (uint32_t)obs_data_get_int(settings, "text_color");
    if (context->dbPath) {
        bfree(context->dbPath);
    }
    context->dbPath = dbPath ? bstrdup(dbPath) : nullptr;
    if (context->selectedType) {
        bfree(context->selectedType);
    }
    context->selectedType = serviceId ? bstrdup(serviceId) : nullptr;
    saveToDatabase(context->dbPath, context->selectedType, title, subtitle, animStyle, themeColor, textColor);
}

obs_properties_t *lowerThirdsGetProperties(void *data) {
    LowerThirdsData *context = (LowerThirdsData *)data;
    obs_properties_t *props = obs_properties_create();
    obs_properties_add_path(props, "database_path", "SQLite Database Path", OBS_PATH_FILE, "*.db", nullptr);
    obs_property_t *serviceList = obs_properties_add_list(props, "active_service", "Active Service", OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);
    obs_property_list_add_string(serviceList, "None", "");
    std::string dbPath = context && context->dbPath ? context->dbPath : getDefaultDbPath();
    sqlite3 *db = nullptr;
    if (sqlite3_open(dbPath.c_str(), &db) == SQLITE_OK) {
        sqlite3_stmt *stmt = nullptr;
        const char *query = "SELECT id, name FROM resources";
        if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                const unsigned char *id = sqlite3_column_text(stmt, 0);
                const unsigned char *name = sqlite3_column_text(stmt, 1);
                if (id && name) {
                    obs_property_list_add_string(serviceList, (const char *)name, (const char *)id);
                }
            }
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }
    obs_property_set_modified_callback(serviceList, activeServiceModifiedCallback);
    obs_properties_add_text(props, "title", "Title", OBS_TEXT_DEFAULT);
    obs_properties_add_text(props, "subtitle", "Subtitle / Info", OBS_TEXT_DEFAULT);
    obs_properties_add_color(props, "theme_color", "Accent Theme Color");
    obs_properties_add_color(props, "text_color", "Text Color");
    obs_property_t *animList = obs_properties_add_list(props, "animation_style", "Animation Style", OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);
    obs_property_list_add_string(animList, "Slide In", "slide");
    obs_property_list_add_string(animList, "Fade In", "fade");
    obs_property_list_add_string(animList, "Elastic Zoom", "zoom");
    return props;
}

struct obs_source_info lowerThirdsSourceInfo = {
    .id = "lower_thirds_swm",
    .type = OBS_SOURCE_TYPE_INPUT,
    .output_flags = OBS_SOURCE_VIDEO,
    .get_name = lowerThirdsGetName,
    .create = lowerThirdsCreate,
    .destroy = lowerThirdsDestroy,
    .get_width = lowerThirdsGetWidth,
    .get_height = lowerThirdsGetHeight,
    .get_properties = lowerThirdsGetProperties,
    .update = lowerThirdsUpdate,
    .video_render = lowerThirdsVideoRender
};
