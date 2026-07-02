#include "ColoredFormatter.h"
#include <sstream>

ColoredFormatter::ColoredFormatter() {
}

ColoredFormatter::~ColoredFormatter() {
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

static std::string levelToAnsiColor(LogLevel level) {
    switch (level) {
        case LogLevel::Trace: return "\033[90m";
        case LogLevel::Debug: return "\033[36m";
        case LogLevel::Info: return "\033[34m";
        case LogLevel::Success: return "\033[1;32m";
        case LogLevel::Warning: return "\033[33m";
        case LogLevel::Error: return "\033[31m";
        case LogLevel::Critical: return "\033[1;31m";
    }
    return "\033[0m";
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

std::string ColoredFormatter::format(const LogEntry &entry) {
    std::ostringstream ss;
    std::string color = levelToAnsiColor(entry.level);
    std::string reset = "\033[0m";
    
    ss << color << "[" << entry.timestamp << "] "
       << "[" << levelToString(entry.level) << "] "
       << "[" << categoryToString(entry.category) << "] "
       << "[Session: " << entry.sessionId << "] "
       << "[Thread: " << entry.threadId << "] "
       << entry.message << reset;
    return ss.str();
}
