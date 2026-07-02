#ifndef MEMORYSINK_H
#define MEMORYSINK_H

#include "ILogSink.h"
#include "../../../core/contracts/IEventBus.h"
#include <mutex>
#include <vector>

class MemorySink : public ILogSink {
public:
    MemorySink(std::shared_ptr<IEventBus> eventBus, int capacityLimit);
    ~MemorySink() override;

    void log(const LogEntry &entry) override;
    bool shouldLog(LogLevel level, LogCategory category) const override;
    void flush() override;
    void setFormatter(std::shared_ptr<ILogFormatter> formatter) override;
    void setFilters(LogLevel minLevel, const std::vector<LogCategory> &categories) override;

    std::vector<LogEntry> getEntries() const;
    void clear();

private:
    std::mutex sinkMutex;
    std::shared_ptr<IEventBus> bus;
    int maxCapacity;
    std::vector<LogEntry> logEntries;
    std::shared_ptr<ILogFormatter> logFormatter;
    LogLevel minimumLevel = LogLevel::Trace;
    std::vector<LogCategory> allowedCategories;
};

#endif
