#ifndef NOTIFICATIONLISTMODEL_H
#define NOTIFICATIONLISTMODEL_H

#include "../../core/contracts/IEventBus.h"
#include "contracts/NotificationSnapshot.h"
#include <QAbstractListModel>
#include <memory>
#include <vector>

namespace swm::runtime::notifications {

class NotificationListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        MessageRole,
        CategoryRole,
        SeverityRole,
        SourceServiceRole,
        LifecycleRole,
        IsReadRole,
        CreatedTimeRole
    };

    explicit NotificationListModel(std::shared_ptr<IEventBus> eventBus, QObject* parent = nullptr);
    ~NotificationListModel() override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void initialize();
    void shutdown();

signals:
    void countChanged();

private:
    void onNotificationChanged(const std::any& payload);

    std::shared_ptr<IEventBus> bus;
    SubscriptionToken eventToken;
    std::vector<NotificationSnapshot> items;
};

} // namespace swm::runtime::notifications

#endif
