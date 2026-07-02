#ifndef MACSTATUSBARLOGVIEWER_H
#define MACSTATUSBARLOGVIEWER_H

#include "../../../core/contracts/IEventBus.h"
#include <memory>
#include <string>
#include <vector>

class MacStatusBarLogViewer {
public:
    MacStatusBarLogViewer(std::shared_ptr<IEventBus> eventBus);
    ~MacStatusBarLogViewer();

    void initialize();

private:
    void onLogAdded(const std::string &formattedLog);
    void updateMenu();

    std::shared_ptr<IEventBus> bus;
    SubscriptionToken token;
    std::vector<std::string> recentLogs;
    void *statusItem;
    void *menuHandler;
};

#endif
