#include "AppBootstrap.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QUrl>
#include <QString>

AppBootstrap::AppBootstrap(QObject *parent) : QObject(parent) {
}

AppBootstrap::~AppBootstrap() {
}

QString AppBootstrap::getAppDir() const {
    return QGuiApplication::applicationDirPath();
}

void AppBootstrap::bootstrap() {
    // Basic Runtime Setup
    QString appDir = QGuiApplication::applicationDirPath();
    
    // Register UI Framework Modules
    qmlEngine.addImportPath(appDir + "/../ui");
    
    // Bind bootstrap for C++ hooks if needed in the future
    qmlEngine.rootContext()->setContextProperty("bootstrap", this);
    
    // Launch PlaygroundApp EXCLUSIVELY
    qmlEngine.load(QUrl::fromLocalFile(appDir + "/../ui/playground/PlaygroundApp.qml"));
}
