#include "RenderSessionManager.h"
#include "GraphicsEngineService.h"

namespace swm::runtime::graphics {

RenderSessionManager::RenderSessionManager(GraphicsEngineService& engineService)
    : m_engineService(engineService), m_idCounter(0) {
}

RenderSessionManager::~RenderSessionManager() {
    destroyAll();
}

RenderSessionId RenderSessionManager::createSession(RenderRequest request) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto id = generateSessionId();
    auto session = std::make_unique<RenderSession>(id, std::move(request), m_engineService);
    session->initialize();
    m_sessions[static_cast<uint64_t>(id)] = std::move(session);
    return id;
}

RenderSession* RenderSessionManager::getSession(RenderSessionId id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_sessions.find(static_cast<uint64_t>(id));
    if (it != m_sessions.end()) {
        return it->second.get();
    }
    return nullptr;
}

void RenderSessionManager::destroySession(RenderSessionId id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_sessions.find(static_cast<uint64_t>(id));
    if (it != m_sessions.end()) {
        it->second->shutdown();
        m_sessions.erase(it);
    }
}

std::vector<RenderSessionId> RenderSessionManager::getActiveSessions() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<RenderSessionId> result;
    for (const auto& pair : m_sessions) {
        if (pair.second->isRunning()) {
            result.push_back(pair.second->sessionId());
        }
    }
    return result;
}

void RenderSessionManager::destroyAll() {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& pair : m_sessions) {
        pair.second->shutdown();
    }
    m_sessions.clear();
}

RenderSessionId RenderSessionManager::generateSessionId() {
    return static_cast<RenderSessionId>(m_idCounter.fetch_add(1) + 1);
}

}
