#include "TextFormatter.h"
#include <sstream>

TextFormatter::TextFormatter() {
}

TextFormatter::~TextFormatter() {
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

std::string TextFormatter::format(const LogEntry &entry) {
    std::ostringstream ss;
    ss << "[" << entry.timestamp << "] "
       << "[" << levelToString(entry.level) << "] "
       << "[" << categoryToString(entry.category) << "] "
       << "[Session: " << entry.sessionId << "] "
       << "[Thread: " << entry.threadId << "] "
       << entry.message;
    return ss.str();
}
