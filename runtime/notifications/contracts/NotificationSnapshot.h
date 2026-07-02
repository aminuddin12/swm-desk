#ifndef NOTIFICATIONSNAPSHOT_H
#define NOTIFICATIONSNAPSHOT_H

#include "NotificationId.h"
#include "NotificationSeverity.h"
#include "NotificationCategory.h"
#include "ServiceId.h"
#include "NotificationLifecycle.h"
#include "NotificationAction.h"
#include <string>
#include <vector>
#include <chrono>

namespace swm::runtime::notifications {

struct NotificationSnapshot {
    NotificationId id;
    std::string title;
    std::string message;
    NotificationCategory category;
    NotificationSeverity severity;
    ServiceId sourceService;
    
    NotificationLifecycle lifecycle{NotificationLifecycle::Active};
    bool isRead{false};
    
    std::chrono::system_clock::time_point createdTime;
    std::chrono::system_clock::time_point expirationTime;
    
    std::vector<NotificationAction> actions;
};

} // namespace swm::runtime::notifications

#endif
