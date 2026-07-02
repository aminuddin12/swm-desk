#include "WindowFactory.h"
#include <QQmlComponent>
#include <QCoreApplication>
#include <QUrl>

QObject* WindowFactory::createWindow(WindowId id, QQmlApplicationEngine *engine, QObject *parent) {
    if (!engine) {
        return nullptr;
    }
    QString appDir = QCoreApplication::applicationDirPath();
    QString path;
    switch (id) {
        case WindowId::LogViewer:
            path = appDir + "/../ui/windows/LogViewerWindow.qml";
            break;
        case WindowId::Settings:
            break;
        case WindowId::About:
            break;
        case WindowId::Dashboard:
            break;
    }
    if (path.isEmpty()) {
        return nullptr;
    }
    QQmlComponent component(engine, QUrl::fromLocalFile(path), parent);
    return component.create();
}
