#ifndef GRAPHICSSTATISTICS_H
#define GRAPHICSSTATISTICS_H

#include <QObject>

namespace swm::runtime::graphics {

class GraphicsRuntime;

class GraphicsStatistics : public QObject {
    Q_OBJECT
    Q_PROPERTY(int frameCount READ getFrameCount NOTIFY statisticsChanged)
    Q_PROPERTY(int renderCount READ getRenderCount NOTIFY statisticsChanged)
    Q_PROPERTY(double lastRenderDurationMs READ getLastRenderDurationMs NOTIFY statisticsChanged)
    Q_PROPERTY(double averageRenderDurationMs READ getAverageRenderDurationMs NOTIFY statisticsChanged)
    Q_PROPERTY(int resolutionWidth READ getResolutionWidth NOTIFY statisticsChanged)
    Q_PROPERTY(int resolutionHeight READ getResolutionHeight NOTIFY statisticsChanged)
    Q_PROPERTY(QString backendName READ getBackendName NOTIFY statisticsChanged)
    Q_PROPERTY(QString engineVersion READ getEngineVersion NOTIFY statisticsChanged)

public:
    explicit GraphicsStatistics(GraphicsRuntime* runtime, QObject* parent = nullptr);

    int getFrameCount() const;
    int getRenderCount() const;
    double getLastRenderDurationMs() const;
    double getAverageRenderDurationMs() const;
    int getResolutionWidth() const;
    int getResolutionHeight() const;
    QString getBackendName() const;
    QString getEngineVersion() const;

public slots:
    void onRuntimeStatisticsChanged();

signals:
    void statisticsChanged();

private:
    GraphicsRuntime* m_runtime;
};

}

#endif
