#include "TaskHandle.h"
#include "../TaskService.h"
#include <utility>

namespace swm::runtime::tasks {

TaskHandle::TaskHandle(TaskId id, std::shared_ptr<TaskService> service)
    : m_id(id), m_service(std::move(service)), m_finished(false) {}

TaskHandle::~TaskHandle() {
    if (!m_finished && m_service) {
        m_service->cancelTask(m_id);
    }
}

TaskHandle::TaskHandle(TaskHandle&& other) noexcept
    : m_id(other.m_id), m_service(std::move(other.m_service)), m_finished(other.m_finished) {
    other.m_finished = true;
}

TaskHandle& TaskHandle::operator=(TaskHandle&& other) noexcept {
    if (this != &other) {
        if (!m_finished && m_service) {
            m_service->cancelTask(m_id);
        }
        m_id = other.m_id;
        m_service = std::move(other.m_service);
        m_finished = other.m_finished;
        other.m_finished = true;
    }
    return *this;
}

void TaskHandle::progress(std::uint8_t percent, std::uint64_t current, std::uint64_t maximum) {
    if (m_service && !m_finished) {
        m_service->updateProgress(m_id, percent, current, maximum);
    }
}

void TaskHandle::message(const std::string& msg) {
    if (m_service && !m_finished) {
        m_service->updateMessage(m_id, msg);
    }
}

void TaskHandle::pause() {
    if (m_service && !m_finished) {
        m_service->pauseTask(m_id);
    }
}

void TaskHandle::resume() {
    if (m_service && !m_finished) {
        m_service->resumeTask(m_id);
    }
}

void TaskHandle::cancel() {
    if (m_service && !m_finished) {
        m_service->cancelTask(m_id);
        m_finished = true;
    }
}

void TaskHandle::complete() {
    if (m_service && !m_finished) {
        m_service->completeTask(m_id);
        m_finished = true;
    }
}

void TaskHandle::fail(const std::string& errorMessage) {
    if (m_service && !m_finished) {
        m_service->failTask(m_id, errorMessage);
        m_finished = true;
    }
}

}
