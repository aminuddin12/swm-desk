#ifndef RENDERSESSIONMANAGER_H
#define RENDERSESSIONMANAGER_H

#include "contracts/RenderSessionId.h"
#include "contracts/RenderRequest.h"
#include "RenderSession.h"
#include <memory>
#include <unordered_map>
#include <vector>
#include <atomic>
#include <mutex>

namespace swm::runtime::graphics {

class GraphicsEngineService;

class RenderSessionManager {
public:
    explicit RenderSessionManager(GraphicsEngineService& engineService);
    ~RenderSessionManager();

    RenderSessionId createSession(RenderRequest request);
    RenderSession* getSession(RenderSessionId id);
    void destroySession(RenderSessionId id);
    std::vector<RenderSessionId> getActiveSessions() const;
    void destroyAll();

private:
    RenderSessionId generateSessionId();

    GraphicsEngineService& m_engineService;
    std::unordered_map<uint64_t, std::unique_ptr<RenderSession>> m_sessions;
    std::atomic<uint64_t> m_idCounter;
    mutable std::mutex m_mutex;
};

}

#endif
