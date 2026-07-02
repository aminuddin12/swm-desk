#ifndef IEVENTBUS_H
#define IEVENTBUS_H

#include "../../runtime/events/RuntimeEvent.h"
#include "../../runtime/events/SubscriptionToken.h"
#include <functional>
#include <any>

class IEventBus {
public:
    virtual ~IEventBus() = default;
    virtual void publish(RuntimeEvent event, const std::any &payload) = 0;
    virtual SubscriptionToken subscribe(RuntimeEvent event, std::function<void(const std::any&)> callback) = 0;
    virtual void unsubscribe(const SubscriptionToken &token) = 0;
};

#endif
