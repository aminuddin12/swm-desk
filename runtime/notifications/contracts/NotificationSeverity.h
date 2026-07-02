#ifndef NOTIFICATIONSEVERITY_H
#define NOTIFICATIONSEVERITY_H

namespace swm::runtime::notifications {

enum class NotificationSeverity {
    Info,
    Success,
    Warning,
    Error,
    Critical
};

} // namespace swm::runtime::notifications

#endif
