#include "AppBootstrap.h"
#include "../runtime/bootstrap/RuntimeBootstrap.h"
#include "../application/services/ServiceRegistry.h"
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
    auto context = RuntimeBootstrap::bootstrap();
    auto logger = context->getLogger();
    
    logger->info("Application Started", LogCategory::Runtime);
    logger->info("Runtime Initialized", LogCategory::Runtime);
    logger->info("Logger Ready", LogCategory::Runtime);
    logger->info("Configuration Loaded", LogCategory::Runtime);
    logger->info("UI Started", LogCategory::Runtime);

    QString appDir = QGuiApplication::applicationDirPath();
    qmlEngine.addImportPath(appDir + "/../ui");
    qmlEngine.rootContext()->setContextProperty("bootstrap", this);
    qmlEngine.load(QUrl::fromLocalFile(appDir + "/../ui/playground/PlaygroundApp.qml"));
}
