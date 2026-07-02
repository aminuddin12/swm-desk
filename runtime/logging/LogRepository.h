#ifndef LOGREPOSITORY_H
#define LOGREPOSITORY_H

#include "../../core/contracts/IRuntimeService.h"
#include "../../core/contracts/IEventBus.h"
#include "LogEntry.h"
#include <mutex>
#include <vector>
#include <memory>

class LogRepository : public IRuntimeService {
public:
    LogRepository(std::shared_ptr<IEventBus> eventBus);
    ~LogRepository() override;

    void initialize() override;
    void start() override;
    void stop() override;
    void shutdown() override;

    std::vector<std::shared_ptr<LogEntry>> getLogs() const;
    std::string getSessionId() const;

private:
    std::shared_ptr<IEventBus> bus;
    SubscriptionToken tokenAdded;
    SubscriptionToken tokenClear;
    std::vector<std::shared_ptr<LogEntry>> logs;
    mutable std::mutex repoMutex;
};

#endif
