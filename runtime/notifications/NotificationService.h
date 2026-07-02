#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include "../../core/contracts/IRuntimeService.h"
#include "../../core/contracts/IEventBus.h"
#include "contracts/NotificationHandle.h"
#include "contracts/NotificationSnapshot.h"
#include "contracts/NotificationRetentionPolicy.h"
#include "NotificationRepository.h"
#include <memory>
#include <string>
#include <atomic>

namespace swm::runtime::notifications {

class NotificationService : public IRuntimeService, public std::enable_shared_from_this<NotificationService> {
public:
    NotificationService(std::shared_ptr<NotificationRepository> repo, std::shared_ptr<IEventBus> eventBus, NotificationRetentionPolicy policy = {});
    ~NotificationService() override = default;

    void initialize() override {}
    void start() override {}
    void stop() override {}
    void shutdown() override {}

    NotificationHandle createNotification(
        ServiceId source,
        NotificationCategory category,
        NotificationSeverity severity,
        const std::string& title,
        const std::string& message,
        const std::vector<NotificationAction>& actions = {}
    );

    // Convenience API (Sugaring)
    NotificationHandle notifyInfo(ServiceId source, NotificationCategory category, const std::string& title, const std::string& message);
    NotificationHandle notifySuccess(ServiceId source, NotificationCategory category, const std::string& title, const std::string& message);
    NotificationHandle notifyWarning(ServiceId source, NotificationCategory category, const std::string& title, const std::string& message);
    NotificationHandle notifyError(ServiceId source, NotificationCategory category, const std::string& title, const std::string& message);
    NotificationHandle notifyCritical(ServiceId source, NotificationCategory category, const std::string& title, const std::string& message);

    // Internal operations used by NotificationHandle
    void dismiss(NotificationId id);
    void markRead(NotificationId id);
    void expire(NotificationId id);
    void remove(NotificationId id);
    void updateMessage(NotificationId id, const std::string& message);
    void updateTitle(NotificationId id, const std::string& title);
    void updateActions(NotificationId id, const std::vector<NotificationAction>& actions);

private:
    void enforceRetentionPolicy();
    void publishChangedEvent(const NotificationSnapshot& snapshot);

    std::shared_ptr<NotificationRepository> repo;
    std::shared_ptr<IEventBus> bus;
    NotificationRetentionPolicy policy;
    std::atomic<uint64_t> idCounter{1};
};

} // namespace swm::runtime::notifications

#endif
