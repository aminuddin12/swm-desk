#include "ConsoleSink.h"
#include <iostream>
#include <algorithm>

ConsoleSink::ConsoleSink() {
}

ConsoleSink::~ConsoleSink() {
}

void ConsoleSink::log(const LogEntry &entry) {
    std::lock_guard<std::mutex> lock(sinkMutex);
    if (logFormatter) {
        std::cout << logFormatter->format(entry) << std::endl;
    }
}

bool ConsoleSink::shouldLog(LogLevel level, LogCategory category) const {
    if (static_cast<int>(level) < static_cast<int>(minimumLevel)) {
        return false;
    }
    if (allowedCategories.empty()) {
        return true;
    }
    return std::find(allowedCategories.begin(), allowedCategories.end(), category) != allowedCategories.end();
}

void ConsoleSink::flush() {
    std::lock_guard<std::mutex> lock(sinkMutex);
    std::cout << std::flush;
}

void ConsoleSink::setFormatter(std::shared_ptr<ILogFormatter> formatter) {
    std::lock_guard<std::mutex> lock(sinkMutex);
    logFormatter = formatter;
}

void ConsoleSink::setFilters(LogLevel minLevel, const std::vector<LogCategory> &categories) {
    std::lock_guard<std::mutex> lock(sinkMutex);
    minimumLevel = minLevel;
    allowedCategories = categories;
}
