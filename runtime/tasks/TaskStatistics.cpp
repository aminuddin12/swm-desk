#include "TaskStatistics.h"

namespace swm::runtime::tasks {

TaskStatistics::TaskStatistics(std::shared_ptr<TaskRepository> repository, std::shared_ptr<IEventBus> eventBus, QObject* parent)
    : QObject(parent), m_repository(std::move(repository)), m_eventBus(std::move(eventBus)) {
    
    m_subscription = m_eventBus->subscribe(RuntimeEvent::TaskChanged, [this](const std::any&) {
        QMetaObject::invokeMethod(this, "refresh", Qt::QueuedConnection);
    });
    
    refresh();
}

TaskStatistics::~TaskStatistics() {
    if (m_eventBus) {
        m_eventBus->unsubscribe(m_subscription);
    }
}

int TaskStatistics::activeTasks() const { return m_activeTasks; }
int TaskStatistics::completedTasks() const { return m_completedTasks; }
int TaskStatistics::failedTasks() const { return m_failedTasks; }

void TaskStatistics::refresh() {
    int active = 0;
    int completed = 0;
    int failed = 0;
    
    auto tasks = m_repository->getAll();
    for (const auto& task : tasks) {
        if (task.state == TaskState::Running || task.state == TaskState::Pending || task.state == TaskState::Paused) {
            active++;
        } else if (task.state == TaskState::Completed) {
            completed++;
        } else if (task.state == TaskState::Failed) {
            failed++;
        }
    }
    
    bool changed = false;
    if (active != m_activeTasks) { m_activeTasks = active; changed = true; }
    if (completed != m_completedTasks) { m_completedTasks = completed; changed = true; }
    if (failed != m_failedTasks) { m_failedTasks = failed; changed = true; }
    
    if (changed) {
        emit statisticsChanged();
    }
}

}
