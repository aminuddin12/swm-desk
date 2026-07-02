#include "NotificationHandle.h"
#include "../NotificationService.h"

namespace swm::runtime::notifications {

NotificationHandle::NotificationHandle(NotificationId id, std::weak_ptr<NotificationService> service)
    : id(id), service(std::move(service)), active(true) {
}

NotificationHandle::~NotificationHandle() {
}

NotificationHandle::NotificationHandle(NotificationHandle&& other) noexcept
    : id(other.id), service(std::move(other.service)), active(other.active) {
    other.active = false;
}

NotificationHandle& NotificationHandle::operator=(NotificationHandle&& other) noexcept {
    if (this != &other) {
        id = other.id;
        service = std::move(other.service);
        active = other.active;
        other.active = false;
    }
    return *this;
}

NotificationId NotificationHandle::getId() const {
    return id;
}

bool NotificationHandle::isValid() const {
    return active && !service.expired();
}

void NotificationHandle::dismiss() {
    if (auto s = service.lock()) {
        s->dismiss(id);
        active = false;
    }
}

void NotificationHandle::markRead() {
    if (auto s = service.lock()) {
        s->markRead(id);
    }
}

void NotificationHandle::expire() {
    if (auto s = service.lock()) {
        s->expire(id);
        active = false;
    }
}

void NotificationHandle::updateMessage(const std::string& message) {
    if (auto s = service.lock()) {
        s->updateMessage(id, message);
    }
}

void NotificationHandle::updateTitle(const std::string& title) {
    if (auto s = service.lock()) {
        s->updateTitle(id, title);
    }
}

void NotificationHandle::updateActions(const std::vector<NotificationAction>& actions) {
    if (auto s = service.lock()) {
        s->updateActions(id, actions);
    }
}

} // namespace swm::runtime::notifications
