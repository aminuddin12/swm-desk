#ifndef NOTIFICATIONLIFECYCLE_H
#define NOTIFICATIONLIFECYCLE_H

namespace swm::runtime::notifications {

enum class NotificationLifecycle {
    Active,
    Dismissed,
    Expired,
    Archived
};

} // namespace swm::runtime::notifications

#endif
