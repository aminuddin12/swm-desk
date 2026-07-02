#include "TaskListModel.h"
#include <algorithm>

namespace swm::runtime::tasks {

TaskListModel::TaskListModel(std::shared_ptr<TaskRepository> repository, std::shared_ptr<IEventBus> eventBus, QObject* parent)
    : QAbstractListModel(parent), m_repository(std::move(repository)), m_eventBus(std::move(eventBus)) {
    
    m_subscription = m_eventBus->subscribe(RuntimeEvent::TaskChanged, [this](const std::any&) {
        QMetaObject::invokeMethod(this, "refresh", Qt::QueuedConnection);
    });
    
    updateFilteredTasks();
}

TaskListModel::~TaskListModel() {
    if (m_eventBus) {
        m_eventBus->unsubscribe(m_subscription);
    }
}

int TaskListModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(m_filteredTasks.size());
}

QVariant TaskListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_filteredTasks.size()) return QVariant();

    const auto& task = m_filteredTasks[index.row()];

    switch (role) {
        case IdRole: return QVariant::fromValue(static_cast<qulonglong>(task.id));
        case NameRole: return QString::fromStdString(task.name);
        case CategoryRole: return static_cast<int>(task.category);
        case StateRole: return static_cast<int>(task.state);
        case PercentRole: return task.progress.percent;
        case CurrentValueRole: return QVariant::fromValue(static_cast<qulonglong>(task.progress.currentValue));
        case MaximumValueRole: return QVariant::fromValue(static_cast<qulonglong>(task.progress.maximumValue));
        case MessageRole: return QString::fromStdString(task.message);
        case CreatedTimeRole: return QVariant::fromValue(task.createdTime.time_since_epoch().count());
        case StartedTimeRole: return QVariant::fromValue(task.startedTime.time_since_epoch().count());
        case FinishedTimeRole: return QVariant::fromValue(task.finishedTime.time_since_epoch().count());
        default: return QVariant();
    }
}

QHash<int, QByteArray> TaskListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "taskId";
    roles[NameRole] = "name";
    roles[CategoryRole] = "category";
    roles[StateRole] = "state";
    roles[PercentRole] = "percent";
    roles[CurrentValueRole] = "currentValue";
    roles[MaximumValueRole] = "maximumValue";
    roles[MessageRole] = "message";
    roles[CreatedTimeRole] = "createdTime";
    roles[StartedTimeRole] = "startedTime";
    roles[FinishedTimeRole] = "finishedTime";
    return roles;
}

int TaskListModel::filterState() const { return m_filterState; }

void TaskListModel::setFilterState(int state) {
    if (m_filterState != state) {
        m_filterState = state;
        refresh();
        emit filterStateChanged();
    }
}

void TaskListModel::refresh() {
    updateFilteredTasks();
}

void TaskListModel::updateFilteredTasks() {
    auto allTasks = m_repository->getAll();
    std::vector<TaskSnapshot> newFiltered;
    
    for (const auto& task : allTasks) {
        if (m_filterState == -1 || static_cast<int>(task.state) == m_filterState) {
            newFiltered.push_back(task);
        }
    }
    
    std::sort(newFiltered.begin(), newFiltered.end(), [](const TaskSnapshot& a, const TaskSnapshot& b) {
        return a.createdTime > b.createdTime;
    });

    beginResetModel();
    m_filteredTasks = std::move(newFiltered);
    endResetModel();
}

}
