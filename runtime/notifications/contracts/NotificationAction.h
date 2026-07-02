#ifndef NOTIFICATIONACTION_H
#define NOTIFICATIONACTION_H

#include "NotificationActionId.h"
#include <string>

namespace swm::runtime::notifications {

struct NotificationAction {
    NotificationActionId id;
    std::string label;
    bool primary{false};
};

} // namespace swm::runtime::notifications

#endif
