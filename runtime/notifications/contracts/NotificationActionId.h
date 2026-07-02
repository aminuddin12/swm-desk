#ifndef NOTIFICATIONACTIONID_H
#define NOTIFICATIONACTIONID_H

namespace swm::runtime::notifications {

enum class NotificationActionId {
    RetryDownload,
    OpenLogs,
    OpenSettings,
    Dismiss,
    InstallPlugin,
    ViewDetails,
    UpdateNow,
    UpdateLater
};

} // namespace swm::runtime::notifications

#endif
