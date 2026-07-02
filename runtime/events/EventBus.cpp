#include "EventBus.h"

EventBus::EventBus() : tokenCounter(1) {
}

EventBus::~EventBus() {
}

void EventBus::publish(RuntimeEvent event, const std::any &payload) {
    std::vector<std::function<void(const std::any&)>> callbacks;
    {
        std::lock_guard<std::mutex> lock(busMutex);
        auto it = subscribers.find(event);
        if (it != subscribers.end()) {
            for (const auto &sub : it->second) {
                callbacks.push_back(sub.callback);
            }
        }
    }
    for (const auto &cb : callbacks) {
        cb(payload);
    }
}

SubscriptionToken EventBus::subscribe(RuntimeEvent event, std::function<void(const std::any&)> callback) {
    std::lock_guard<std::mutex> lock(busMutex);
    SubscriptionToken token{tokenCounter.fetch_add(1)};
    subscribers[event].push_back({token, callback});
    return token;
}

void EventBus::unsubscribe(const SubscriptionToken &token) {
    std::lock_guard<std::mutex> lock(busMutex);
    for (auto &pair : subscribers) {
        auto &list = pair.second;
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->token.id == token.id) {
                list.erase(it);
                return;
            }
        }
    }
}
