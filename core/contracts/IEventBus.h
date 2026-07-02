#ifndef IEVENTBUS_H
#define IEVENTBUS_H

#include "../../runtime/events/RuntimeEvent.h"
#include "../../runtime/events/SubscriptionToken.h"
#include <functional>
#include <string>

class IEventBus {
public:
    virtual ~IEventBus() = default;
    virtual void publish(RuntimeEvent event, const std::string &payload) = 0;
    virtual SubscriptionToken subscribe(RuntimeEvent event, std::function<void(const std::string&)> callback) = 0;
    virtual void unsubscribe(const SubscriptionToken &token) = 0;
};

#endif
