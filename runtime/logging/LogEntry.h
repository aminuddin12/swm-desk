#ifndef LOGENTRY_H
#define LOGENTRY_H

#include "LogLevel.h"
#include "LogCategory.h"
#include <string>
#include <cstdint>

struct LogEntry {
    std::string timestamp;
    LogLevel level;
    LogCategory category;
    std::string message;
    std::string sessionId;
    uint32_t processId;
    std::string threadId;
    std::string platform;
    std::string applicationVersion;
};

#endif
