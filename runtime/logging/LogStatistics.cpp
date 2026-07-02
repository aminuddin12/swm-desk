#include "LogStatistics.h"
#include "LogEntry.h"
#include <QDateTime>

LogStatistics::LogStatistics(std::shared_ptr<IEventBus> eventBus, QObject *parent)
    : QObject(parent), bus(eventBus) {
}

LogStatistics::~LogStatistics() {
    shutdown();
}

void LogStatistics::initialize() {
}

void LogStatistics::start() {
    if (bus) {
        tokenAdded = bus->subscribe(RuntimeEvent::LogAdded, [this](const std::any &payload) {
            auto entry = std::any_cast<std::shared_ptr<LogEntry>>(payload);
            m_totalLogs++;
            emit totalLogsChanged();

            switch (entry->level) {
                case LogLevel::Trace: m_traceCount++; emit traceCountChanged(); break;
                case LogLevel::Debug: m_debugCount++; emit debugCountChanged(); break;
                case LogLevel::Info: m_infoCount++; emit infoCountChanged(); break;
                case LogLevel::Success: break;
                case LogLevel::Warning: m_warnCount++; emit warnCountChanged(); break;
                case LogLevel::Error: m_errorCount++; emit errorCountChanged(); break;
                case LogLevel::Critical: m_criticalCount++; emit criticalCountChanged(); break;
            }

            m_lastFlush = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
            emit lastFlushChanged();
        });

        tokenCleared = bus->subscribe(RuntimeEvent::ClearMemoryLogs, [this](const std::any &payload) {
            (void)payload;
            m_totalLogs = 0;
            m_traceCount = 0;
            m_debugCount = 0;
            m_infoCount = 0;
            m_warnCount = 0;
            m_errorCount = 0;
            m_criticalCount = 0;
            m_lastFlush = "-";
            emit totalLogsChanged();
            emit traceCountChanged();
            emit debugCountChanged();
            emit infoCountChanged();
            emit warnCountChanged();
            emit errorCountChanged();
            emit criticalCountChanged();
            emit lastFlushChanged();
        });
    }
}

void LogStatistics::stop() {
    if (bus) {
        bus->unsubscribe(tokenAdded);
        bus->unsubscribe(tokenCleared);
    }
}

void LogStatistics::shutdown() {
    stop();
}
