#pragma once

#include "TaskRepository.h"
#include "../../../core/contracts/IEventBus.h"
#include <QObject>
#include <memory>

namespace swm::runtime::tasks {

class TaskStatistics : public QObject {
    Q_OBJECT
    Q_PROPERTY(int activeTasks READ activeTasks NOTIFY statisticsChanged)
    Q_PROPERTY(int completedTasks READ completedTasks NOTIFY statisticsChanged)
    Q_PROPERTY(int failedTasks READ failedTasks NOTIFY statisticsChanged)

public:
    TaskStatistics(std::shared_ptr<TaskRepository> repository, std::shared_ptr<IEventBus> eventBus, QObject* parent = nullptr);
    ~TaskStatistics() override;

    int activeTasks() const;
    int completedTasks() const;
    int failedTasks() const;

public slots:
    void refresh();

signals:
    void statisticsChanged();

private:
    std::shared_ptr<TaskRepository> m_repository;
    std::shared_ptr<IEventBus> m_eventBus;
    SubscriptionToken m_subscription;
    
    int m_activeTasks{0};
    int m_completedTasks{0};
    int m_failedTasks{0};
};

}
