#ifndef ILOGGER_H
#define ILOGGER_H

#include "LogLevel.h"
#include "LogCategory.h"
#include <string>

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void trace(const std::string &message, LogCategory category) = 0;
    virtual void debug(const std::string &message, LogCategory category) = 0;
    virtual void info(const std::string &message, LogCategory category) = 0;
    virtual void success(const std::string &message, LogCategory category) = 0;
    virtual void warning(const std::string &message, LogCategory category) = 0;
    virtual void error(const std::string &message, LogCategory category) = 0;
    virtual void critical(const std::string &message, LogCategory category) = 0;
};

#endif
