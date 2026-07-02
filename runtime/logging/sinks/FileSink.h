#ifndef FILESINK_H
#define FILESINK_H

#include "ILogSink.h"
#include <fstream>
#include <mutex>
#include <string>

class FileSink : public ILogSink {
public:
    FileSink(const std::string &logsDirectory);
    ~FileSink() override;

    void log(const LogEntry &entry) override;
    bool shouldLog(LogLevel level, LogCategory category) const override;
    void flush() override;
    void setFormatter(std::shared_ptr<ILogFormatter> formatter) override;
    void setFilters(LogLevel minLevel, const std::vector<LogCategory> &categories) override;

private:
    void openFile(const std::string &dateStr);

    std::mutex sinkMutex;
    std::string logsDir;
    std::ofstream fileStream;
    std::string currentFileDate;
    std::shared_ptr<ILogFormatter> logFormatter;
    LogLevel minimumLevel = LogLevel::Trace;
    std::vector<LogCategory> allowedCategories;
    bool isActive = true;
    int retryCounter = 0;
};

#endif
