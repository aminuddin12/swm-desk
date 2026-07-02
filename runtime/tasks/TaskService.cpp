#include "TaskService.h"
#include <chrono>

namespace swm::runtime::tasks {

TaskService::TaskService(std::shared_ptr<TaskRepository> repository, std::shared_ptr<IEventBus> eventBus)
    : m_repository(std::move(repository)), m_eventBus(std::move(eventBus)) {}

TaskHandle TaskService::createTask(const std::string& name, TaskCategory category) {
    TaskId id = generateNextId();
    
    TaskSnapshot snapshot;
    snapshot.id = id;
    snapshot.name = name;
    snapshot.category = category;
    snapshot.state = TaskState::Pending;
    snapshot.createdTime = std::chrono::system_clock::now();
    
    m_repository->insert(snapshot);
    dispatchEvent(snapshot);
    
    return TaskHandle(id, shared_from_this());
}

void TaskService::updateProgress(TaskId id, std::uint8_t percent, std::uint64_t current, std::uint64_t maximum) {
    if (auto taskOpt = m_repository->find(id)) {
        TaskSnapshot snapshot = *taskOpt;
        if (snapshot.state == TaskState::Pending) {
            snapshot.state = TaskState::Running;
            snapshot.startedTime = std::chrono::system_clock::now();
        }
        snapshot.progress.percent = percent;
        snapshot.progress.currentValue = current;
        snapshot.progress.maximumValue = maximum;
        
        m_repository->replace(snapshot);
        dispatchEvent(snapshot);
    }
}

void TaskService::updateMessage(TaskId id, const std::string& message) {
    if (auto taskOpt = m_repository->find(id)) {
        TaskSnapshot snapshot = *taskOpt;
        snapshot.message = message;
        m_repository->replace(snapshot);
        dispatchEvent(snapshot);
    }
}

void TaskService::updateStateInternal(TaskId id, TaskState newState, const std::string& message) {
    if (auto taskOpt = m_repository->find(id)) {
        TaskSnapshot snapshot = *taskOpt;
        snapshot.state = newState;
        if (!message.empty()) {
            snapshot.message = message;
        }
        if (newState == TaskState::Completed || newState == TaskState::Failed || newState == TaskState::Cancelled) {
            snapshot.finishedTime = std::chrono::system_clock::now();
        } else if (newState == TaskState::Running && snapshot.startedTime.time_since_epoch().count() == 0) {
            snapshot.startedTime = std::chrono::system_clock::now();
        }
        
        m_repository->replace(snapshot);
        dispatchEvent(snapshot);
    }
}

void TaskService::pauseTask(TaskId id) {
    updateStateInternal(id, TaskState::Paused, "");
}

void TaskService::resumeTask(TaskId id) {
    updateStateInternal(id, TaskState::Running, "");
}

void TaskService::cancelTask(TaskId id) {
    updateStateInternal(id, TaskState::Cancelled, "");
}

void TaskService::completeTask(TaskId id) {
    updateStateInternal(id, TaskState::Completed, "");
}

void TaskService::failTask(TaskId id, const std::string& errorMessage) {
    updateStateInternal(id, TaskState::Failed, errorMessage);
}

void TaskService::dispatchEvent(const TaskSnapshot& snapshot) {
    m_eventBus->publish(RuntimeEvent::TaskChanged, std::make_any<TaskSnapshot>(snapshot));
}

TaskId TaskService::generateNextId() {
    return m_idCounter.fetch_add(1, std::memory_order_relaxed);
}

}
