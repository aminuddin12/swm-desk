#ifndef MACSTATUSBARSERVICE_H
#define MACSTATUSBARSERVICE_H

#include "../../../core/contracts/IRuntimeService.h"
#include "../../../core/contracts/IEventBus.h"
#include <memory>
#include <vector>
#include <string>

class MacStatusBarService : public IRuntimeService {
public:
    MacStatusBarService(std::shared_ptr<IEventBus> eventBus);
    ~MacStatusBarService() override;

    void initialize() override;
    void start() override;
    void stop() override;
    void shutdown() override;

    void publishClearLogs();
    void publishOpenLogViewer();

private:
    void updateMenu();
    void onLogAdded(const std::string &logMessage);

    std::shared_ptr<IEventBus> bus;
    SubscriptionToken token;
    SubscriptionToken tokenCleared;
    std::vector<std::string> recentLogs;
    void *statusItem;
    void *menuHandler;
};

#endif
