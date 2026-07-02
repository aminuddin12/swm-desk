#pragma once

#include "TaskId.h"
#include <string>
#include <memory>
#include <cstdint>

namespace swm::runtime::tasks {

class TaskService;

class TaskHandle {
public:
    TaskHandle() = default;
    TaskHandle(TaskId id, std::shared_ptr<TaskService> service);
    ~TaskHandle();

    TaskHandle(const TaskHandle&) = delete;
    TaskHandle& operator=(const TaskHandle&) = delete;

    TaskHandle(TaskHandle&& other) noexcept;
    TaskHandle& operator=(TaskHandle&& other) noexcept;

    TaskId getId() const { return m_id; }

    void progress(std::uint8_t percent, std::uint64_t current = 0, std::uint64_t maximum = 0);
    void message(const std::string& msg);
    void pause();
    void resume();
    void cancel();
    void complete();
    void fail(const std::string& errorMessage = "");

private:
    TaskId m_id{0};
    std::shared_ptr<TaskService> m_service;
    bool m_finished{true};
};

}
