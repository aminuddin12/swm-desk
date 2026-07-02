#include "MemorySink.h"
#include <algorithm>

MemorySink::MemorySink(std::shared_ptr<IEventBus> eventBus, int capacityLimit)
    : bus(eventBus), maxCapacity(capacityLimit) {
}

MemorySink::~MemorySink() {
}

void MemorySink::log(const LogEntry &entry) {
    std::string formattedPayload;
    {
        std::lock_guard<std::mutex> lock(sinkMutex);
        if (logFormatter) {
            formattedPayload = logFormatter->format(entry);
        } else {
            formattedPayload = entry.message;
        }

        if (maxCapacity > 0 && static_cast<int>(logEntries.size()) >= maxCapacity) {
            logEntries.erase(logEntries.begin());
        }
        logEntries.push_back(entry);
    }

    if (bus) {
        bus->publish(RuntimeEvent::LogAdded, formattedPayload);
    }
}

bool MemorySink::shouldLog(LogLevel level, LogCategory category) const {
    if (static_cast<int>(level) < static_cast<int>(minimumLevel)) {
        return false;
    }
    if (allowedCategories.empty()) {
        return true;
    }
    return std::find(allowedCategories.begin(), allowedCategories.end(), category) != allowedCategories.end();
}

void MemorySink::flush() {
}

void MemorySink::setFormatter(std::shared_ptr<ILogFormatter> formatter) {
    std::lock_guard<std::mutex> lock(sinkMutex);
    logFormatter = formatter;
}

void MemorySink::setFilters(LogLevel minLevel, const std::vector<LogCategory> &categories) {
    std::lock_guard<std::mutex> lock(sinkMutex);
    minimumLevel = minLevel;
    allowedCategories = categories;
}

std::vector<LogEntry> MemorySink::getEntries() const {
    auto *mutableThis = const_cast<MemorySink*>(this);
    std::lock_guard<std::mutex> lock(mutableThis->sinkMutex);
    return logEntries;
}
