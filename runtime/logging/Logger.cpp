#include "Logger.h"
#include "../../application/services/ServiceRegistry.h"
#include "../../core/contracts/IEnvironment.h"
#include "../../core/contracts/IEventBus.h"
#include "sinks/ConsoleSink.h"
#include "sinks/FileSink.h"
#include "sinks/MemorySink.h"
#include "Formatter/ColoredFormatter.h"
#include "Formatter/TextFormatter.h"
#include <QUuid>
#include <QCoreApplication>
#include <QDateTime>
#include <chrono>
#include <sstream>

Logger::Logger(const LoggingConfig &config)
    : loggingConfig(config),
      logQueue(config.bufferSize, QueueFullPolicy::DropOldest),
      running(false),
      shutdownFlag(false) {
    sessionId = QUuid::createUuid().toString().toStdString();
    processId = static_cast<uint32_t>(QCoreApplication::applicationPid());
#if defined(Q_OS_MAC)
    platformName = "macOS";
#elif defined(Q_OS_WIN)
    platformName = "Windows";
#else
    platformName = "Linux";
#endif
    appVersion = "1.0.0";
}

Logger::~Logger() {
    shutdown();
}

void Logger::initialize() {
    auto &registry = ServiceRegistry::instance();
    auto env = std::any_cast<std::shared_ptr<IEnvironment>>(registry.resolve("IEnvironment"));
    auto bus = std::any_cast<std::shared_ptr<IEventBus>>(registry.resolve("IEventBus"));

    auto console = std::make_shared<ConsoleSink>();
    console->setFormatter(std::make_shared<ColoredFormatter>());
    addSink(console);

    if (env) {
        auto file = std::make_shared<FileSink>(env->getLogsPath());
        file->setFormatter(std::make_shared<TextFormatter>());
        addSink(file);
    }

    if (bus) {
        auto memory = std::make_shared<MemorySink>(bus, loggingConfig.bufferSize);
        memory->setFormatter(std::make_shared<TextFormatter>());
        addSink(memory);
    }
}

void Logger::start() {
    std::lock_guard<std::mutex> lock(loggerMutex);
    if (running) {
        return;
    }
    running = true;
    shutdownFlag = false;
    worker = std::thread(&Logger::workerLoop, this);
}

void Logger::stop() {
    shutdown();
}

void Logger::shutdown() {
    {
        std::lock_guard<std::mutex> lock(loggerMutex);
        if (!running) {
            return;
        }
        running = false;
        shutdownFlag = true;
    }
    logQueue.shutdown();
    if (worker.joinable()) {
        worker.join();
    }
}

void Logger::trace(const std::string &message, LogCategory category) {
    log(LogLevel::Trace, category, message);
}

void Logger::debug(const std::string &message, LogCategory category) {
    log(LogLevel::Debug, category, message);
}

void Logger::info(const std::string &message, LogCategory category) {
    log(LogLevel::Info, category, message);
}

void Logger::success(const std::string &message, LogCategory category) {
    log(LogLevel::Success, category, message);
}

void Logger::warning(const std::string &message, LogCategory category) {
    log(LogLevel::Warning, category, message);
}

void Logger::error(const std::string &message, LogCategory category) {
    log(LogLevel::Error, category, message);
}

void Logger::critical(const std::string &message, LogCategory category) {
    log(LogLevel::Critical, category, message);
}

void Logger::addSink(std::shared_ptr<ILogSink> sink) {
    std::lock_guard<std::mutex> lock(loggerMutex);
    sinks.push_back(sink);
}

void Logger::log(LogLevel level, LogCategory category, const std::string &message) {
    if (shutdownFlag) {
        return;
    }
    std::ostringstream ss;
    ss << std::this_thread::get_id();
    
    LogEntry entry;
    entry.timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz").toStdString();
    entry.level = level;
    entry.category = category;
    entry.message = message;
    entry.sessionId = sessionId;
    entry.processId = processId;
    entry.threadId = ss.str();
    entry.platform = platformName;
    entry.applicationVersion = appVersion;
    
    logQueue.push(entry);
}

void Logger::dispatch(const LogEntry &entry) {
    std::vector<std::shared_ptr<ILogSink>> activeSinks;
    {
        std::lock_guard<std::mutex> lock(loggerMutex);
        activeSinks = sinks;
    }
    for (const auto &sink : activeSinks) {
        if (sink->shouldLog(entry.level, entry.category)) {
            sink->log(entry);
        }
    }
}

void Logger::flushSinks() {
    std::vector<std::shared_ptr<ILogSink>> activeSinks;
    {
        std::lock_guard<std::mutex> lock(loggerMutex);
        activeSinks = sinks;
    }
    for (const auto &sink : activeSinks) {
        sink->flush();
    }
}

void Logger::workerLoop() {
    LogEntry entry;
    int unprocessedCount = 0;
    auto lastFlushTime = std::chrono::steady_clock::now();
    
    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFlushTime);
        auto remainingTimeout = std::chrono::milliseconds(loggingConfig.flushIntervalMs) - elapsed;
        if (remainingTimeout.count() <= 0) {
            remainingTimeout = std::chrono::milliseconds(1);
        }
        
        bool hasEntry = logQueue.popTimeout(entry, remainingTimeout);
        
        if (hasEntry) {
            dispatch(entry);
            unprocessedCount++;
            
            if (unprocessedCount >= loggingConfig.flushLogCount) {
                flushSinks();
                unprocessedCount = 0;
                lastFlushTime = std::chrono::steady_clock::now();
            }
        }
        
        now = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFlushTime);
        if (elapsed.count() >= loggingConfig.flushIntervalMs) {
            flushSinks();
            unprocessedCount = 0;
            lastFlushTime = std::chrono::steady_clock::now();
        }
        
        if (!hasEntry && shutdownFlag) {
            while (logQueue.pop(entry)) {
                dispatch(entry);
            }
            flushSinks();
            break;
        }
    }
}
