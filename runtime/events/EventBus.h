#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "../../core/contracts/IEventBus.h"
#include <mutex>
#include <unordered_map>
#include <vector>
#include <atomic>

class EventBus : public IEventBus {
public:
    EventBus();
    ~EventBus() override;

    void publish(RuntimeEvent event, const std::any &payload) override;
    SubscriptionToken subscribe(RuntimeEvent event, std::function<void(const std::any&)> callback) override;
    void unsubscribe(const SubscriptionToken &token) override;

private:
    struct Subscriber {
        SubscriptionToken token;
        std::function<void(const std::any&)> callback;
    };

    std::mutex busMutex;
    std::atomic<uint64_t> tokenCounter;
    std::unordered_map<RuntimeEvent, std::vector<Subscriber>> subscribers;
};

#endif
