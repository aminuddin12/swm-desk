#ifndef NOTIFICATIONSTATISTICS_H
#define NOTIFICATIONSTATISTICS_H

#include "../../core/contracts/IRuntimeService.h"
#include "../../core/contracts/IEventBus.h"
#include "contracts/NotificationSnapshot.h"
#include <QObject>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <atomic>

namespace swm::runtime::notifications {

class NotificationStatistics : public QObject, public IRuntimeService {
    Q_OBJECT
    Q_PROPERTY(int total READ getTotal NOTIFY statisticsChanged)
    Q_PROPERTY(int unread READ getUnread NOTIFY statisticsChanged)
    Q_PROPERTY(int active READ getActive NOTIFY statisticsChanged)
    Q_PROPERTY(int dismissed READ getDismissed NOTIFY statisticsChanged)
    Q_PROPERTY(int warning READ getWarning NOTIFY statisticsChanged)
    Q_PROPERTY(int error READ getError NOTIFY statisticsChanged)
    Q_PROPERTY(int critical READ getCritical NOTIFY statisticsChanged)

public:
    explicit NotificationStatistics(std::shared_ptr<IEventBus> eventBus, QObject* parent = nullptr);
    ~NotificationStatistics() override;

    void initialize() override;
    void start() override;
    void stop() override;
    void shutdown() override;

    int getTotal() const;
    int getUnread() const;
    int getActive() const;
    int getDismissed() const;
    int getWarning() const;
    int getError() const;
    int getCritical() const;

signals:
    void statisticsChanged();

private:
    void onNotificationChanged(const std::any& payload);

    std::shared_ptr<IEventBus> bus;
    SubscriptionToken eventToken;

    struct StateSummary {
        NotificationLifecycle lifecycle;
        NotificationSeverity severity;
        bool isRead;
    };

    std::unordered_map<NotificationId, StateSummary> knownStates;
    mutable std::mutex statsMutex;

    int total{0};
    int unread{0};
    int active{0};
    int dismissed{0};
    int warning{0};
    int error{0};
    int critical{0};
};

} // namespace swm::runtime::notifications

#endif
