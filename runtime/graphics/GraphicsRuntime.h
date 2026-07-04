#ifndef GRAPHICSRUNTIME_H
#define GRAPHICSRUNTIME_H

#include "../../core/contracts/IRuntimeService.h"
#include "../../core/contracts/IEventBus.h"
#include "contracts/ISceneBuilder.h"
#include "contracts/RenderRequest.h"
#include "contracts/RenderSessionId.h"
#include "contracts/GraphicsFrameSnapshot.h"
#include <QObject>
#include <memory>
#include <vector>

namespace swm::runtime::graphics {

class GraphicsEngineService;
class RenderSessionManager;
class RenderScheduler;
class IGraphicsResourceService;

class GraphicsRuntime : public QObject, public IRuntimeService {
    Q_OBJECT
    Q_PROPERTY(quint64 defaultPreviewSessionId READ getDefaultPreviewSessionId CONSTANT)

public:
    explicit GraphicsRuntime(std::shared_ptr<IEventBus> eventBus, std::shared_ptr<ISceneBuilder> sceneBuilder, QObject* parent = nullptr);
    ~GraphicsRuntime() override;

    void initialize() override;
    void start() override;
    void stop() override;
    void shutdown() override;

    RenderSessionId createSession(RenderRequest request);
    void destroySession(RenderSessionId id);
    void requestRender(RenderSessionId id);

    uint64_t getFrameCount() const;
    uint64_t getRenderCount() const;
    uint64_t getLastRenderDurationNs() const;
    uint64_t getAverageRenderDurationNs() const;
    uint32_t getResolutionWidth() const;
    uint32_t getResolutionHeight() const;
    std::string getBackendName() const;
    std::string getEngineVersion() const;
    quint64 getDefaultPreviewSessionId() const;

    GraphicsFrameSnapshot getLastSnapshot(RenderSessionId id) const;

signals:
    void frameAvailable(swm::runtime::graphics::RenderSessionId id);
    void statisticsChanged();

private:
    std::shared_ptr<IEventBus> m_eventBus;
    std::shared_ptr<ISceneBuilder> m_sceneBuilder;

    std::unique_ptr<GraphicsEngineService> m_engineService;
    std::unique_ptr<RenderSessionManager> m_sessionManager;
    std::unique_ptr<RenderScheduler> m_scheduler;
    std::unique_ptr<IGraphicsResourceService> m_resourceService;

    RenderSessionId m_defaultPreviewSessionId;
};

}

#endif
