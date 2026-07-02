#ifndef NOTIFICATIONRETENTIONPOLICY_H
#define NOTIFICATIONRETENTIONPOLICY_H

#include <chrono>

namespace swm::runtime::notifications {

struct NotificationRetentionPolicy {
    size_t maximumNotifications{1000};
    size_t maximumActiveNotifications{10};
    size_t maximumUnread{500};
    size_t maximumHistory{5000};
    
    std::chrono::seconds expirationDuration{std::chrono::hours(24)};
    std::chrono::seconds autoDismissDuration{std::chrono::seconds(10)};
};

} // namespace swm::runtime::notifications

#endif
