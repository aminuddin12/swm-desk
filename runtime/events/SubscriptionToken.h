#ifndef SUBSCRIPTIONTOKEN_H
#define SUBSCRIPTIONTOKEN_H

#include <cstdint>

struct SubscriptionToken {
    uint64_t id;
    
    bool operator==(const SubscriptionToken &other) const {
        return id == other.id;
    }
};

#endif
