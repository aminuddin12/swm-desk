#ifndef LOGGER_H
#define LOGGER_H

#include "ILogger.h"
#include "../../core/contracts/IRuntimeService.h"
#include "../../core/contracts/IConfiguration.h"
#include "../threading/BlockingQueue.h"
#include "sinks/ILogSink.h"
#include <mutex>
#include <vector>
#include <thread>
#include <atomic>

class Logger : public ILogger, public IRuntimeService {
public:
    Logger(const LoggingConfig &config);
    ~Logger() override;

    void initialize() override;
    void start() override;
    void stop() override;
    void shutdown() override;

    void trace(const std::string &message, LogCategory category) override;
    void debug(const std::string &message, LogCategory category) override;
    void info(const std::string &message, LogCategory category) override;
    void success(const std::string &message, LogCategory category) override;
    void warning(const std::string &message, LogCategory category) override;
    void error(const std::string &message, LogCategory category) override;
    void critical(const std::string &message, LogCategory category) override;

    void addSink(std::shared_ptr<ILogSink> sink);

private:
    void log(LogLevel level, LogCategory category, const std::string &message);
    void workerLoop();
    void dispatch(const LogEntry &entry);
    void flushSinks();

    LoggingConfig loggingConfig;
    std::string sessionId;
    uint32_t processId;
    std::string platformName;
    std::string appVersion;

    BlockingQueue<LogEntry> logQueue;
    std::vector<std::shared_ptr<ILogSink>> sinks;
    std::mutex loggerMutex;
    std::thread worker;
    std::atomic<bool> running;
    std::atomic<bool> shutdownFlag;
};

#endif
