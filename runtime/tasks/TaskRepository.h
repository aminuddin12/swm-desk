#pragma once

#include "contracts/TaskSnapshot.h"
#include <vector>
#include <optional>
#include <mutex>
#include <unordered_map>

namespace swm::runtime::tasks {

class TaskRepository {
public:
    TaskRepository() = default;
    ~TaskRepository() = default;

    TaskRepository(const TaskRepository&) = delete;
    TaskRepository& operator=(const TaskRepository&) = delete;

    void insert(const TaskSnapshot& snapshot);
    void replace(const TaskSnapshot& snapshot);
    void erase(TaskId id);
    
    std::optional<TaskSnapshot> find(TaskId id) const;
    std::vector<TaskSnapshot> getAll() const;

private:
    mutable std::mutex m_mutex;
    std::unordered_map<TaskId, TaskSnapshot> m_tasks;
};

}
