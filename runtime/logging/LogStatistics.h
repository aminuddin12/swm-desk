#ifndef LOGSTATISTICS_H
#define LOGSTATISTICS_H

#include <QObject>
#include "../../core/contracts/IEventBus.h"
#include "../../core/contracts/IRuntimeService.h"
#include <memory>

class LogStatistics : public QObject, public IRuntimeService {
    Q_OBJECT
    Q_PROPERTY(int totalLogs READ totalLogs NOTIFY totalLogsChanged)
    Q_PROPERTY(int traceCount READ traceCount NOTIFY traceCountChanged)
    Q_PROPERTY(int debugCount READ debugCount NOTIFY debugCountChanged)
    Q_PROPERTY(int infoCount READ infoCount NOTIFY infoCountChanged)
    Q_PROPERTY(int warnCount READ warnCount NOTIFY warnCountChanged)
    Q_PROPERTY(int errorCount READ errorCount NOTIFY errorCountChanged)
    Q_PROPERTY(int criticalCount READ criticalCount NOTIFY criticalCountChanged)
    Q_PROPERTY(int queueSize READ queueSize NOTIFY queueSizeChanged)
    Q_PROPERTY(int droppedLogs READ droppedLogs NOTIFY droppedLogsChanged)
    Q_PROPERTY(int flushCount READ flushCount NOTIFY flushCountChanged)
    Q_PROPERTY(QString lastFlush READ lastFlush NOTIFY lastFlushChanged)

public:
    explicit LogStatistics(std::shared_ptr<IEventBus> eventBus, QObject *parent = nullptr);
    ~LogStatistics() override;

    void initialize() override;
    void start() override;
    void stop() override;
    void shutdown() override;

    int totalLogs() const { return m_totalLogs; }
    int traceCount() const { return m_traceCount; }
    int debugCount() const { return m_debugCount; }
    int infoCount() const { return m_infoCount; }
    int warnCount() const { return m_warnCount; }
    int errorCount() const { return m_errorCount; }
    int criticalCount() const { return m_criticalCount; }
    int queueSize() const { return m_queueSize; }
    int droppedLogs() const { return m_droppedLogs; }
    int flushCount() const { return m_flushCount; }
    QString lastFlush() const { return m_lastFlush; }

signals:
    void totalLogsChanged();
    void traceCountChanged();
    void debugCountChanged();
    void infoCountChanged();
    void warnCountChanged();
    void errorCountChanged();
    void criticalCountChanged();
    void queueSizeChanged();
    void droppedLogsChanged();
    void flushCountChanged();
    void lastFlushChanged();

private:
    std::shared_ptr<IEventBus> bus;
    SubscriptionToken tokenAdded;
    SubscriptionToken tokenCleared;

    int m_totalLogs = 0;
    int m_traceCount = 0;
    int m_debugCount = 0;
    int m_infoCount = 0;
    int m_warnCount = 0;
    int m_errorCount = 0;
    int m_criticalCount = 0;
    int m_queueSize = 0;
    int m_droppedLogs = 0;
    int m_flushCount = 0;
    QString m_lastFlush = "-";
};

#endif
