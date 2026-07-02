#ifndef ILOGSINK_H
#define ILOGSINK_H

#include "../LogEntry.h"
#include "../Formatter/ILogFormatter.h"
#include <memory>
#include <vector>

class ILogSink {
public:
    virtual ~ILogSink() = default;
    virtual void log(const LogEntry &entry) = 0;
    virtual bool shouldLog(LogLevel level, LogCategory category) const = 0;
    virtual void flush() = 0;
    virtual void setFormatter(std::shared_ptr<ILogFormatter> formatter) = 0;
    virtual void setFilters(LogLevel minLevel, const std::vector<LogCategory> &categories) = 0;
};

#endif
