#include "NotificationService.h"
#include "../../runtime/events/RuntimeEvent.h"
#include <chrono>
#include <algorithm>

namespace swm::runtime::notifications {

NotificationService::NotificationService(std::shared_ptr<NotificationRepository> repo, std::shared_ptr<IEventBus> eventBus, NotificationRetentionPolicy policy)
    : repo(std::move(repo)), bus(std::move(eventBus)), policy(policy) {
}

NotificationHandle NotificationService::createNotification(
    ServiceId source,
    NotificationCategory category,
    NotificationSeverity severity,
    const std::string& title,
    const std::string& message,
    const std::vector<NotificationAction>& actions) 
{
    NotificationSnapshot snapshot;
    snapshot.id = idCounter.fetch_add(1, std::memory_order_relaxed);
    snapshot.title = title;
    snapshot.message = message;
    snapshot.category = category;
    snapshot.severity = severity;
    snapshot.sourceService = source;
    snapshot.lifecycle = NotificationLifecycle::Active;
    snapshot.isRead = false;
    snapshot.createdTime = std::chrono::system_clock::now();
    snapshot.expirationTime = snapshot.createdTime + policy.expirationDuration;
    snapshot.actions = actions;

    repo->insert(snapshot);
    enforceRetentionPolicy();
    publishChangedEvent(snapshot);

    return NotificationHandle(snapshot.id, weak_from_this());
}

NotificationHandle NotificationService::notifyInfo(ServiceId source, NotificationCategory category, const std::string& title, const std::string& message) {
    return createNotification(source, category, NotificationSeverity::Info, title, message);
}

NotificationHandle NotificationService::notifySuccess(ServiceId source, NotificationCategory category, const std::string& title, const std::string& message) {
    return createNotification(source, category, NotificationSeverity::Success, title, message);
}

NotificationHandle NotificationService::notifyWarning(ServiceId source, NotificationCategory category, const std::string& title, const std::string& message) {
    return createNotification(source, category, NotificationSeverity::Warning, title, message);
}

NotificationHandle NotificationService::notifyError(ServiceId source, NotificationCategory category, const std::string& title, const std::string& message) {
    return createNotification(source, category, NotificationSeverity::Error, title, message);
}

NotificationHandle NotificationService::notifyCritical(ServiceId source, NotificationCategory category, const std::string& title, const std::string& message) {
    return createNotification(source, category, NotificationSeverity::Critical, title, message);
}

void NotificationService::dismiss(NotificationId id) {
    auto snapshotOpt = repo->tryFind(id);
    if (snapshotOpt && snapshotOpt->lifecycle == NotificationLifecycle::Active) {
        snapshotOpt->lifecycle = NotificationLifecycle::Dismissed;
        snapshotOpt->isRead = true; // Auto mark read if dismissed
        repo->replace(*snapshotOpt);
        publishChangedEvent(*snapshotOpt);
    }
}

void NotificationService::markRead(NotificationId id) {
    auto snapshotOpt = repo->tryFind(id);
    if (snapshotOpt && !snapshotOpt->isRead) {
        snapshotOpt->isRead = true;
        repo->replace(*snapshotOpt);
        publishChangedEvent(*snapshotOpt);
    }
}

void NotificationService::expire(NotificationId id) {
    auto snapshotOpt = repo->tryFind(id);
    if (snapshotOpt && snapshotOpt->lifecycle != NotificationLifecycle::Expired) {
        snapshotOpt->lifecycle = NotificationLifecycle::Expired;
        repo->replace(*snapshotOpt);
        publishChangedEvent(*snapshotOpt);
    }
}

void NotificationService::remove(NotificationId id) {
    if (repo->contains(id)) {
        repo->erase(id);
        // Note: Currently no specific event for removal, the list model will pick it up or we can fire a deletion event.
        // For simplicity, we can fire a changed event with Archived lifecycle if we want to notify deletion.
        NotificationSnapshot phantom;
        phantom.id = id;
        phantom.lifecycle = NotificationLifecycle::Archived;
        publishChangedEvent(phantom);
    }
}

void NotificationService::updateMessage(NotificationId id, const std::string& message) {
    auto snapshotOpt = repo->tryFind(id);
    if (snapshotOpt) {
        snapshotOpt->message = message;
        repo->replace(*snapshotOpt);
        publishChangedEvent(*snapshotOpt);
    }
}

void NotificationService::updateTitle(NotificationId id, const std::string& title) {
    auto snapshotOpt = repo->tryFind(id);
    if (snapshotOpt) {
        snapshotOpt->title = title;
        repo->replace(*snapshotOpt);
        publishChangedEvent(*snapshotOpt);
    }
}

void NotificationService::updateActions(NotificationId id, const std::vector<NotificationAction>& actions) {
    auto snapshotOpt = repo->tryFind(id);
    if (snapshotOpt) {
        snapshotOpt->actions = actions;
        repo->replace(*snapshotOpt);
        publishChangedEvent(*snapshotOpt);
    }
}

void NotificationService::publishChangedEvent(const NotificationSnapshot& snapshot) {
    if (bus) {
        bus->publish(RuntimeEvent::NotificationChanged, snapshot);
    }
}

void NotificationService::enforceRetentionPolicy() {
    auto all = repo->getAll();
    if (all.size() > policy.maximumHistory) {
        // Sort by oldest first
        std::sort(all.begin(), all.end(), [](const NotificationSnapshot& a, const NotificationSnapshot& b) {
            return a.createdTime < b.createdTime;
        });
        
        size_t toRemove = all.size() - policy.maximumHistory;
        for (size_t i = 0; i < toRemove; ++i) {
            remove(all[i].id);
        }
    }
}

} // namespace swm::runtime::notifications
