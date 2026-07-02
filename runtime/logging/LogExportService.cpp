#include "LogExportService.h"
#include "../../application/services/ServiceRegistry.h"
#include "LogRepository.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

LogExportService::LogExportService(QObject *parent) : QObject(parent) {
}

LogExportService::~LogExportService() {
}

static std::string levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Trace: return "TRACE";
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info: return "INFO";
        case LogLevel::Success: return "SUCCESS";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error: return "ERROR";
        case LogLevel::Critical: return "CRITICAL";
    }
    return "UNKNOWN";
}

static std::string categoryToString(LogCategory category) {
    switch (category) {
        case LogCategory::Runtime: return "Runtime";
        case LogCategory::OBS: return "OBS";
        case LogCategory::UI: return "UI";
        case LogCategory::Plugin: return "Plugin";
        case LogCategory::Marketplace: return "Marketplace";
    }
    return "Unknown";
}

void LogExportService::exportLogs(const QString &filePath, const QString &format) {
    auto &registry = ServiceRegistry::instance();
    if (!registry.contains("LogRepository")) {
        return;
    }

    auto repo = std::any_cast<std::shared_ptr<LogRepository>>(registry.resolve("LogRepository"));
    if (!repo) {
        return;
    }

    auto logs = repo->getLogs();
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);

    if (format.toLower() == "json") {
        out << "[\n";
        for (size_t i = 0; i < logs.size(); ++i) {
            const auto &entry = logs[i];
            out << "  {\n"
                << "    \"timestamp\": \"" << QString::fromStdString(entry->timestamp) << "\",\n"
                << "    \"level\": \"" << QString::fromStdString(levelToString(entry->level)) << "\",\n"
                << "    \"category\": \"" << QString::fromStdString(categoryToString(entry->category)) << "\",\n"
                << "    \"message\": \"" << QString::fromStdString(entry->message) << "\"\n"
                << "  }";
            if (i < logs.size() - 1) {
                out << ",";
            }
            out << "\n";
        }
        out << "]\n";
    } else {
        for (const auto &entry : logs) {
            out << "[" << QString::fromStdString(entry->timestamp) << "] "
                << "[" << QString::fromStdString(levelToString(entry->level)) << "] "
                << "[" << QString::fromStdString(categoryToString(entry->category)) << "] "
                << QString::fromStdString(entry->message) << "\n";
        }
    }
}
