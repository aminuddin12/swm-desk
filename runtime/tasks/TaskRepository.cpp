#include "TaskRepository.h"

namespace swm::runtime::tasks {

void TaskRepository::insert(const TaskSnapshot& snapshot) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_tasks[snapshot.id] = snapshot;
}

void TaskRepository::replace(const TaskSnapshot& snapshot) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_tasks[snapshot.id] = snapshot;
}

void TaskRepository::erase(TaskId id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_tasks.erase(id);
}

std::optional<TaskSnapshot> TaskRepository::find(TaskId id) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (auto it = m_tasks.find(id); it != m_tasks.end()) {
        return it->second;
    }
    return std::nullopt;
}

std::vector<TaskSnapshot> TaskRepository::getAll() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<TaskSnapshot> result;
    result.reserve(m_tasks.size());
    for (const auto& [_, task] : m_tasks) {
        result.push_back(task);
    }
    return result;
}

}
