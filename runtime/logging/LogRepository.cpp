#include "LogRepository.h"
#include "sinks/MemorySink.h"
#include "../../application/services/ServiceRegistry.h"

LogRepository::LogRepository(std::shared_ptr<IEventBus> eventBus) : bus(eventBus) {
}

LogRepository::~LogRepository() {
    shutdown();
}

void LogRepository::initialize() {
}

void LogRepository::start() {
    if (bus) {
        tokenAdded = bus->subscribe(RuntimeEvent::LogAdded, [this](const std::any &payload) {
            auto entry = std::any_cast<std::shared_ptr<LogEntry>>(payload);
            std::lock_guard<std::mutex> lock(repoMutex);
            logs.push_back(entry);
        });

        tokenClear = bus->subscribe(RuntimeEvent::ClearMemoryLogs, [this](const std::any &payload) {
            (void)payload;
            {
                std::lock_guard<std::mutex> lock(repoMutex);
                logs.clear();
            }
            if (bus) {
                bus->publish(RuntimeEvent::MemoryLogsCleared, std::any());
            }
        });
    }
}

void LogRepository::stop() {
    if (bus) {
        bus->unsubscribe(tokenAdded);
        bus->unsubscribe(tokenClear);
    }
}

void LogRepository::shutdown() {
    stop();
}

std::vector<std::shared_ptr<LogEntry>> LogRepository::getLogs() const {
    std::lock_guard<std::mutex> lock(repoMutex);
    return logs;
}

std::string LogRepository::getSessionId() const {
    std::lock_guard<std::mutex> lock(repoMutex);
    if (!logs.empty()) {
        return logs[0]->sessionId;
    }
    return "";
}
