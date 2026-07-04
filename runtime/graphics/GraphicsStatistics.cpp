#include "GraphicsStatistics.h"
#include "GraphicsRuntime.h"

namespace swm::runtime::graphics {

GraphicsStatistics::GraphicsStatistics(GraphicsRuntime* runtime, QObject* parent)
    : QObject(parent), m_runtime(runtime) {
    
    if (m_runtime) {
        connect(m_runtime, &GraphicsRuntime::statisticsChanged,
                this, &GraphicsStatistics::onRuntimeStatisticsChanged);
    }
}

int GraphicsStatistics::getFrameCount() const {
    return m_runtime ? static_cast<int>(m_runtime->getFrameCount()) : 0;
}

int GraphicsStatistics::getRenderCount() const {
    return m_runtime ? static_cast<int>(m_runtime->getRenderCount()) : 0;
}

double GraphicsStatistics::getLastRenderDurationMs() const {
    return m_runtime ? static_cast<double>(m_runtime->getLastRenderDurationNs()) / 1000000.0 : 0.0;
}

double GraphicsStatistics::getAverageRenderDurationMs() const {
    return m_runtime ? static_cast<double>(m_runtime->getAverageRenderDurationNs()) / 1000000.0 : 0.0;
}

int GraphicsStatistics::getResolutionWidth() const {
    return m_runtime ? static_cast<int>(m_runtime->getResolutionWidth()) : 0;
}

int GraphicsStatistics::getResolutionHeight() const {
    return m_runtime ? static_cast<int>(m_runtime->getResolutionHeight()) : 0;
}

QString GraphicsStatistics::getBackendName() const {
    return m_runtime ? QString::fromStdString(m_runtime->getBackendName()) : QString();
}

QString GraphicsStatistics::getEngineVersion() const {
    return m_runtime ? QString::fromStdString(m_runtime->getEngineVersion()) : QString();
}

void GraphicsStatistics::onRuntimeStatisticsChanged() {
    emit statisticsChanged();
}

}
