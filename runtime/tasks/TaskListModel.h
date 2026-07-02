#pragma once

#include "TaskRepository.h"
#include "../../../core/contracts/IEventBus.h"
#include <QAbstractListModel>
#include <memory>
#include <vector>

namespace swm::runtime::tasks {

class TaskListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int filterState READ filterState WRITE setFilterState NOTIFY filterStateChanged)

public:
    enum TaskRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CategoryRole,
        StateRole,
        PercentRole,
        CurrentValueRole,
        MaximumValueRole,
        MessageRole,
        CreatedTimeRole,
        StartedTimeRole,
        FinishedTimeRole
    };

    TaskListModel(std::shared_ptr<TaskRepository> repository, std::shared_ptr<IEventBus> eventBus, QObject* parent = nullptr);
    ~TaskListModel() override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    int filterState() const;
    void setFilterState(int state);

public slots:
    void refresh();

signals:
    void filterStateChanged();

private:
    void updateFilteredTasks();

    std::shared_ptr<TaskRepository> m_repository;
    std::shared_ptr<IEventBus> m_eventBus;
    SubscriptionToken m_subscription;
    
    std::vector<TaskSnapshot> m_filteredTasks;
    int m_filterState{-1};
};

}
