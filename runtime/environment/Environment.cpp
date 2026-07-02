#include "Environment.h"
#include <QStandardPaths>
#include <QDir>

Environment::Environment() {
    QDir().mkpath(QString::fromStdString(getApplicationDataPath()));
    QDir().mkpath(QString::fromStdString(getCachePath()));
    QDir().mkpath(QString::fromStdString(getLogsPath()));
    QDir().mkpath(QString::fromStdString(getPluginsPath()));
    QDir().mkpath(QString::fromStdString(getAssetsPath()));
    QDir().mkpath(QString::fromStdString(getTemplatesPath()));
    QDir().mkpath(QString::fromStdString(getMarketplacePath()));
    QDir().mkpath(QString::fromStdString(getDownloadsPath()));
    QDir().mkpath(QString::fromStdString(getConfigPath()));
}

Environment::~Environment() {
}

std::string Environment::getApplicationDataPath() const {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    if (path.isEmpty()) {
        path = QDir::homePath() + "/.swmdesk";
    }
    return path.toStdString();
}

std::string Environment::getCachePath() const {
    return getApplicationDataPath() + "/cache";
}

std::string Environment::getLogsPath() const {
    return getApplicationDataPath() + "/logs";
}

std::string Environment::getPluginsPath() const {
    return getApplicationDataPath() + "/plugins";
}

std::string Environment::getAssetsPath() const {
    return getApplicationDataPath() + "/assets";
}

std::string Environment::getTemplatesPath() const {
    return getApplicationDataPath() + "/templates";
}

std::string Environment::getMarketplacePath() const {
    return getApplicationDataPath() + "/marketplace";
}

std::string Environment::getDownloadsPath() const {
    return getApplicationDataPath() + "/downloads";
}

std::string Environment::getConfigPath() const {
    return getApplicationDataPath() + "/config";
}
