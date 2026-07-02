#include "NotificationListModel.h"
#include "../../runtime/events/RuntimeEvent.h"
#include <QString>

namespace swm::runtime::notifications {

NotificationListModel::NotificationListModel(std::shared_ptr<IEventBus> eventBus, QObject* parent)
    : QAbstractListModel(parent), bus(std::move(eventBus)) {
}

NotificationListModel::~NotificationListModel() {
    shutdown();
}

void NotificationListModel::initialize() {
    if (bus) {
        eventToken = bus->subscribe(
            RuntimeEvent::NotificationChanged,
            [this](const std::any& payload) {
                // Must be invoked on the main thread for UI safety
                QMetaObject::invokeMethod(this, [this, payload]() {
                    this->onNotificationChanged(payload);
                }, Qt::QueuedConnection);
            }
        );
    }
}

void NotificationListModel::shutdown() {
    if (bus && eventToken.id != 0) {
        bus->unsubscribe(eventToken);
        eventToken.id = 0;
    }
}

void NotificationListModel::onNotificationChanged(const std::any& payload) {
    if (payload.type() != typeid(NotificationSnapshot)) return;
    auto snapshot = std::any_cast<NotificationSnapshot>(payload);

    auto it = std::find_if(items.begin(), items.end(),
        [&snapshot](const NotificationSnapshot& s) { return s.id == snapshot.id; });

    if (snapshot.lifecycle == NotificationLifecycle::Archived) {
        if (it != items.end()) {
            int row = std::distance(items.begin(), it);
            beginRemoveRows(QModelIndex(), row, row);
            items.erase(it);
            endRemoveRows();
            emit countChanged();
        }
        return;
    }

    if (it != items.end()) {
        int row = std::distance(items.begin(), it);
        *it = snapshot;
        emit dataChanged(index(row, 0), index(row, 0));
    } else {
        // Insert at the beginning (newest first)
        beginInsertRows(QModelIndex(), 0, 0);
        items.insert(items.begin(), snapshot);
        endInsertRows();
        emit countChanged();
    }
}

int NotificationListModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(items.size());
}

QVariant NotificationListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= items.size()) return QVariant();

    const auto& item = items[index.row()];

    switch (role) {
        case IdRole: return static_cast<qulonglong>(item.id);
        case TitleRole: return QString::fromStdString(item.title);
        case MessageRole: return QString::fromStdString(item.message);
        case CategoryRole: return static_cast<int>(item.category);
        case SeverityRole: return static_cast<int>(item.severity);
        case SourceServiceRole: return static_cast<int>(item.sourceService);
        case LifecycleRole: return static_cast<int>(item.lifecycle);
        case IsReadRole: return item.isRead;
        case CreatedTimeRole: return static_cast<qulonglong>(std::chrono::duration_cast<std::chrono::milliseconds>(item.createdTime.time_since_epoch()).count());
        default: return QVariant();
    }
}

QHash<int, QByteArray> NotificationListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TitleRole] = "title";
    roles[MessageRole] = "message";
    roles[CategoryRole] = "category";
    roles[SeverityRole] = "severity";
    roles[SourceServiceRole] = "sourceService";
    roles[LifecycleRole] = "lifecycle";
    roles[IsReadRole] = "isRead";
    roles[CreatedTimeRole] = "createdTime";
    return roles;
}

} // namespace swm::runtime::notifications
