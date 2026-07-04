#ifndef GRAPHICSPREVIEWITEM_H
#define GRAPHICSPREVIEWITEM_H

#include <QQuickPaintedItem>
#include <QImage>
#include "contracts/RenderSessionId.h"

namespace swm::runtime::graphics {

class GraphicsRuntime;

class GraphicsPreviewItem : public QQuickPaintedItem {
    Q_OBJECT

public:
    explicit GraphicsPreviewItem(QQuickItem* parent = nullptr);
    ~GraphicsPreviewItem() override = default;

    void paint(QPainter* painter) override;

    Q_INVOKABLE void setRuntime(QObject* runtime);
    
    Q_INVOKABLE void setSessionId(quint64 id);
    Q_INVOKABLE void renderOnce();
    Q_INVOKABLE void startRender();
    Q_INVOKABLE void stopRender();

public slots:
    void onFrameAvailable(swm::runtime::graphics::RenderSessionId id);

private:
    GraphicsRuntime* m_runtime = nullptr;
    RenderSessionId m_sessionId{0};
    QImage m_currentImage;
};

}

#endif
