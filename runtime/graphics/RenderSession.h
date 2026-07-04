#ifndef RENDERSESSION_H
#define RENDERSESSION_H

#include "contracts/RenderSessionId.h"
#include "contracts/RenderRequest.h"
#include "contracts/GraphicsFrameSnapshot.h"
#include <memory>
#include <cstdint>
#include <atomic>
#include <chrono>

namespace swm::runtime::graphics {

class GraphicsEngineService;

class RenderSession {
public:
    RenderSession(RenderSessionId id, RenderRequest request, GraphicsEngineService& engineService);
    ~RenderSession();

    RenderSessionId sessionId() const;
    const RenderRequest& getRequest() const;

    void initialize();
    void start();
    void pause();
    void resume();
    void stop();
    void shutdown();

    GraphicsFrameSnapshot render();
    GraphicsFrameSnapshot getLastSnapshot() const;

    uint64_t getFrameCount() const;
    uint64_t getRenderCount() const;
    bool isRunning() const;
    bool isPaused() const;

private:
    RenderSessionId m_id;
    RenderRequest m_request;
    GraphicsEngineService& m_engineService;

    std::atomic<bool> m_running;
    std::atomic<bool> m_paused;
    std::atomic<uint64_t> m_frameCount;
    std::atomic<uint64_t> m_renderCount;
    uint64_t m_totalRenderDurationNs = 0;

    GraphicsFrameSnapshot m_lastSnapshot;
};

}

#endif
