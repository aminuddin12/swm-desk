#include "MemorySink.h"
#include <algorithm>

MemorySink::MemorySink(std::shared_ptr<IEventBus> eventBus, int capacityLimit)
    : bus(eventBus), maxCapacity(capacityLimit) {
    if (bus) {
        bus->subscribe(RuntimeEvent::ClearMemoryLogs, [this](const std::any &payload) {
            (void)payload;
            clear();
        });
    }
}

MemorySink::~MemorySink() {
}

void MemorySink::log(const LogEntry &entry) {
    auto sharedEntry = std::make_shared<LogEntry>(entry);
    {
        std::lock_guard<std::mutex> lock(sinkMutex);
        if (maxCapacity > 0 && static_cast<int>(logEntries.size()) >= maxCapacity) {
            logEntries.erase(logEntries.begin());
        }
        logEntries.push_back(*sharedEntry);
    }
    if (bus) {
        bus->publish(RuntimeEvent::LogAdded, sharedEntry);
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

void MemorySink::clear() {
    std::lock_guard<std::mutex> lock(sinkMutex);
    logEntries.clear();
}
