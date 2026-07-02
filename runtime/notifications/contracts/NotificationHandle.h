#ifndef NOTIFICATIONHANDLE_H
#define NOTIFICATIONHANDLE_H

#include "NotificationId.h"
#include "NotificationAction.h"
#include <string>
#include <vector>
#include <memory>

namespace swm::runtime::notifications {

class NotificationService;

class NotificationHandle {
public:
    NotificationHandle(NotificationId id, std::weak_ptr<NotificationService> service);
    ~NotificationHandle();

    NotificationHandle(const NotificationHandle&) = delete;
    NotificationHandle& operator=(const NotificationHandle&) = delete;

    NotificationHandle(NotificationHandle&& other) noexcept;
    NotificationHandle& operator=(NotificationHandle&& other) noexcept;

    NotificationId getId() const;
    bool isValid() const;

    void dismiss();
    void markRead();
    void expire();

    void updateMessage(const std::string& message);
    void updateTitle(const std::string& title);
    void updateActions(const std::vector<NotificationAction>& actions);

private:
    NotificationId id;
    std::weak_ptr<NotificationService> service;
    bool active;
};

} // namespace swm::runtime::notifications

#endif
