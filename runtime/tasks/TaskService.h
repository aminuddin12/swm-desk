#pragma once

#include "contracts/TaskSnapshot.h"
#include "contracts/TaskHandle.h"
#include "TaskRepository.h"
#include "../../../core/contracts/IEventBus.h"
#include <memory>
#include <atomic>

namespace swm::runtime::tasks {

class TaskService : public std::enable_shared_from_this<TaskService> {
public:
    TaskService(std::shared_ptr<TaskRepository> repository, std::shared_ptr<IEventBus> eventBus);
    ~TaskService() = default;

    TaskService(const TaskService&) = delete;
    TaskService& operator=(const TaskService&) = delete;

    TaskHandle createTask(const std::string& name, TaskCategory category);

    void updateProgress(TaskId id, std::uint8_t percent, std::uint64_t current, std::uint64_t maximum);
    void updateMessage(TaskId id, const std::string& message);
    void pauseTask(TaskId id);
    void resumeTask(TaskId id);
    void cancelTask(TaskId id);
    void completeTask(TaskId id);
    void failTask(TaskId id, const std::string& errorMessage);

private:
    void dispatchEvent(const TaskSnapshot& snapshot);
    TaskId generateNextId();
    void updateStateInternal(TaskId id, TaskState newState, const std::string& message = "");

    std::shared_ptr<TaskRepository> m_repository;
    std::shared_ptr<IEventBus> m_eventBus;
    std::atomic<TaskId> m_idCounter{1};
};

}
