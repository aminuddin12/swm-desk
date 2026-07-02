#ifndef NOTIFICATIONCATEGORY_H
#define NOTIFICATIONCATEGORY_H

namespace swm::runtime::notifications {

enum class NotificationCategory {
    Runtime,
    Download,
    Upload,
    Plugin,
    Marketplace,
    OBS,
    AI,
    Update,
    System
};

} // namespace swm::runtime::notifications

#endif
