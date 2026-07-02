#ifndef CONSOLESINK_H
#define CONSOLESINK_H

#include "ILogSink.h"
#include <mutex>

class ConsoleSink : public ILogSink {
public:
    ConsoleSink();
    ~ConsoleSink() override;

    void log(const LogEntry &entry) override;
    bool shouldLog(LogLevel level, LogCategory category) const override;
    void flush() override;
    void setFormatter(std::shared_ptr<ILogFormatter> formatter) override;
    void setFilters(LogLevel minLevel, const std::vector<LogCategory> &categories) override;

private:
    std::mutex sinkMutex;
    std::shared_ptr<ILogFormatter> logFormatter;
    LogLevel minimumLevel = LogLevel::Trace;
    std::vector<LogCategory> allowedCategories;
};

#endif
