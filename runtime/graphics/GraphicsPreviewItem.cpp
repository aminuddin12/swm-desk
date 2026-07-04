#include "GraphicsPreviewItem.h"
#include "GraphicsRuntime.h"
#include <swm/Frame.h>
#include <QPainter>

namespace swm::runtime::graphics {

GraphicsPreviewItem::GraphicsPreviewItem(QQuickItem* parent)
    : QQuickPaintedItem(parent) {
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

void GraphicsPreviewItem::setRuntime(QObject* runtimeObj) {
    auto runtime = qobject_cast<swm::runtime::graphics::GraphicsRuntime*>(runtimeObj);
    if (m_runtime) {
        disconnect(m_runtime, &GraphicsRuntime::frameAvailable,
                   this, &GraphicsPreviewItem::onFrameAvailable);
    }

    m_runtime = runtime;

    if (m_runtime) {
        connect(m_runtime, &GraphicsRuntime::frameAvailable,
                this, &GraphicsPreviewItem::onFrameAvailable);
    }
}

void GraphicsPreviewItem::setSessionId(quint64 id) {
    m_sessionId = static_cast<RenderSessionId>(id);
}

void GraphicsPreviewItem::renderOnce() {
    if (m_runtime) {
        m_runtime->requestRender(m_sessionId);
    }
}

void GraphicsPreviewItem::startRender() {
    // Stub for continuous rendering
}

void GraphicsPreviewItem::stopRender() {
    // Stub for continuous rendering
}

void GraphicsPreviewItem::onFrameAvailable(RenderSessionId id) {
    if (id != m_sessionId || !m_runtime) {
        return;
    }

    auto snapshot = m_runtime->getLastSnapshot(id);
    if (!snapshot.frame) {
        return;
    }

    const uint8_t* data = snapshot.frame->data();
    uint32_t width = snapshot.frame->width();
    uint32_t height = snapshot.frame->height();

    // Zero-copy read wrapper
    m_currentImage = QImage(data, width, height, QImage::Format_RGBA8888).copy();
    
    update();
}

void GraphicsPreviewItem::paint(QPainter* painter) {
    if (!m_currentImage.isNull()) {
        painter->drawImage(boundingRect(), m_currentImage);
    } else {
        painter->fillRect(boundingRect(), QColor(30, 30, 30));
    }
}

}
