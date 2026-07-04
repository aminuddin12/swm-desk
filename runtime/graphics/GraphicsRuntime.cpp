#include "GraphicsRuntime.h"
#include "GraphicsEngineService.h"
#include "RenderSessionManager.h"
#include "RenderScheduler.h"
#include "GraphicsResourceService.h"
#include "ValidationSceneBuilder.h"
#include "../events/RuntimeEvent.h"
#include <QMetaObject>

namespace swm::runtime::graphics {

GraphicsRuntime::GraphicsRuntime(std::shared_ptr<IEventBus> eventBus, std::shared_ptr<ISceneBuilder> sceneBuilder, QObject* parent)
    : QObject(parent),
      m_eventBus(std::move(eventBus)),
      m_sceneBuilder(std::move(sceneBuilder)),
      m_defaultPreviewSessionId(static_cast<RenderSessionId>(0)) {
    
    qRegisterMetaType<swm::runtime::graphics::RenderSessionId>("swm::runtime::graphics::RenderSessionId");
}

GraphicsRuntime::~GraphicsRuntime() {
    shutdown();
}

void GraphicsRuntime::initialize() {
    m_engineService = std::make_unique<GraphicsEngineService>(1920, 1080);
    m_sessionManager = std::make_unique<RenderSessionManager>(*m_engineService);
    m_scheduler = std::make_unique<RenderScheduler>();
    m_resourceService = std::make_unique<GraphicsResourceService>();

    m_engineService->initialize();
}

void GraphicsRuntime::start() {
    if (!m_sceneBuilder) {
        m_sceneBuilder = std::make_shared<ValidationSceneBuilder>();
    }

    RenderRequest previewRequest;
    previewRequest.canvas = m_sceneBuilder->build();
    previewRequest.outputType = RenderOutputType::Preview;
    previewRequest.width = 1920;
    previewRequest.height = 1080;

    m_defaultPreviewSessionId = m_sessionManager->createSession(previewRequest);
    
    auto* session = m_sessionManager->getSession(m_defaultPreviewSessionId);
    if (session) {
        session->start();
    }
}

void GraphicsRuntime::stop() {
    if (m_sessionManager) {
        m_sessionManager->destroyAll();
    }
}

void GraphicsRuntime::shutdown() {
    stop();
    if (m_engineService) {
        m_engineService->shutdown();
    }
}

RenderSessionId GraphicsRuntime::createSession(RenderRequest request) {
    if (m_sessionManager) {
        return m_sessionManager->createSession(std::move(request));
    }
    return static_cast<RenderSessionId>(0);
}

void GraphicsRuntime::destroySession(RenderSessionId id) {
    if (m_sessionManager) {
        m_sessionManager->destroySession(id);
    }
}

void GraphicsRuntime::requestRender(RenderSessionId id) {
    if (!m_sessionManager) {
        return;
    }
    
    auto* session = m_sessionManager->getSession(id);
    if (session) {
        session->render();
        
        QMetaObject::invokeMethod(this, [this, id]() {
            emit frameAvailable(id);
            emit statisticsChanged();
        }, Qt::QueuedConnection);
        
        if (m_eventBus) {
            m_eventBus->publish(RuntimeEvent::GraphicsFrameAvailable, std::any());
        }
    }
}

uint64_t GraphicsRuntime::getFrameCount() const {
    if (m_sessionManager) {
        auto* session = m_sessionManager->getSession(m_defaultPreviewSessionId);
        if (session) return session->getFrameCount();
    }
    return 0;
}

uint64_t GraphicsRuntime::getRenderCount() const {
    if (m_sessionManager) {
        auto* session = m_sessionManager->getSession(m_defaultPreviewSessionId);
        if (session) return session->getRenderCount();
    }
    return 0;
}

uint64_t GraphicsRuntime::getLastRenderDurationNs() const {
    if (m_sessionManager) {
        auto* session = m_sessionManager->getSession(m_defaultPreviewSessionId);
        if (session) return session->getLastSnapshot().renderDurationNs;
    }
    return 0;
}

uint64_t GraphicsRuntime::getAverageRenderDurationNs() const {
    return getLastRenderDurationNs();
}

uint32_t GraphicsRuntime::getResolutionWidth() const {
    if (m_engineService) return m_engineService->getWidth();
    return 0;
}

uint32_t GraphicsRuntime::getResolutionHeight() const {
    if (m_engineService) return m_engineService->getHeight();
    return 0;
}

std::string GraphicsRuntime::getBackendName() const {
    if (m_engineService) return m_engineService->getBackendName();
    return "";
}

std::string GraphicsRuntime::getEngineVersion() const {
    if (m_engineService) return m_engineService->getEngineVersion();
    return "";
}

quint64 GraphicsRuntime::getDefaultPreviewSessionId() const {
    return static_cast<quint64>(m_defaultPreviewSessionId);
}

GraphicsFrameSnapshot GraphicsRuntime::getLastSnapshot(RenderSessionId id) const {
    if (m_sessionManager) {
        auto* session = m_sessionManager->getSession(id);
        if (session) {
            return session->getLastSnapshot();
        }
    }
    return GraphicsFrameSnapshot{nullptr, 0, 0, 0};
}

}
