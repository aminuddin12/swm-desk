#include "RenderSession.h"
#include "GraphicsEngineService.h"
#include <chrono>

namespace swm::runtime::graphics {

RenderSession::RenderSession(RenderSessionId id, RenderRequest request, GraphicsEngineService& engineService)
    : m_id(id),
      m_request(std::move(request)),
      m_engineService(engineService),
      m_running(false),
      m_paused(false),
      m_frameCount(0),
      m_renderCount(0),
      m_lastSnapshot{nullptr, 0, 0, 0} {
}

RenderSession::~RenderSession() {
    shutdown();
}

RenderSessionId RenderSession::sessionId() const {
    return m_id;
}

const RenderRequest& RenderSession::getRequest() const {
    return m_request;
}

void RenderSession::initialize() {
}

void RenderSession::start() {
    m_running = true;
    m_paused = false;
}

void RenderSession::pause() {
    m_paused = true;
}

void RenderSession::resume() {
    m_paused = false;
}

void RenderSession::stop() {
    m_running = false;
    m_paused = false;
}

void RenderSession::shutdown() {
    stop();
}

GraphicsFrameSnapshot RenderSession::render() {
    auto startTime = std::chrono::steady_clock::now();

    auto frame = m_engineService.render(m_request.document);

    auto endTime = std::chrono::steady_clock::now();
    auto durationNs = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count());

    uint64_t sequence = m_frameCount.fetch_add(1) + 1;
    m_renderCount.fetch_add(1);
    m_totalRenderDurationNs += durationNs;

    auto timestampNs = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            startTime.time_since_epoch()).count());

    m_lastSnapshot = GraphicsFrameSnapshot{frame, durationNs, sequence, timestampNs};

    return m_lastSnapshot;
}

GraphicsFrameSnapshot RenderSession::getLastSnapshot() const {
    return m_lastSnapshot;
}

uint64_t RenderSession::getFrameCount() const {
    return m_frameCount.load();
}

uint64_t RenderSession::getRenderCount() const {
    return m_renderCount.load();
}

bool RenderSession::isRunning() const {
    return m_running.load();
}

bool RenderSession::isPaused() const {
    return m_paused.load();
}

}
