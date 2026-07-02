#include "AppBootstrap.h"
#include "../runtime/bootstrap/RuntimeBootstrap.h"
#include "../application/services/ServiceRegistry.h"
#include "../runtime/logging/LogStatistics.h"
#include "../runtime/logging/LogExportService.h"
#include "../runtime/logging/LogListModel.h"
#include "../runtime/bootstrap/WindowManager.h"
#include "../runtime/tasks/TaskListModel.h"
#include "../runtime/tasks/TaskStatistics.h"
#include "../runtime/tasks/TaskListModel.h"
#include "../runtime/notifications/NotificationStatistics.h"
#include "../runtime/notifications/NotificationListModel.h"
#include "../runtime/tasks/TaskService.h"
#include "../runtime/tasks/TaskRepository.h"
#include "menu/ApplicationMenuBuilder.h"
#include <QCoreApplication>
#include <QQmlContext>
#include <QUrl>
#include <QString>

AppBootstrap::AppBootstrap(QObject *parent) : QObject(parent) {
}

AppBootstrap::~AppBootstrap() {
}

QString AppBootstrap::getAppDir() const {
    return QCoreApplication::applicationDirPath();
}

void AppBootstrap::bootstrap() {
    auto context = RuntimeBootstrap::bootstrap();
    auto logger = context->getLogger();
    
    auto &registry = ServiceRegistry::instance();
    auto winMgr = std::any_cast<std::shared_ptr<WindowManager>>(registry.resolve("WindowManager"));
    if (winMgr) {
        winMgr->setEngine(&qmlEngine);
    }

    ApplicationMenuBuilder menuBuilder;
    menuBuilder.build(context->getEventBus());

    auto stats = std::any_cast<std::shared_ptr<LogStatistics>>(registry.resolve("LogStatistics"));
    logExport = new LogExportService(this);
    
    auto taskStats = std::any_cast<std::shared_ptr<swm::runtime::tasks::TaskStatistics>>(registry.resolve("TaskStatistics"));
    auto taskListModel = std::any_cast<std::shared_ptr<swm::runtime::tasks::TaskListModel>>(registry.resolve("TaskListModel"));

    qmlRegisterType<LogListModel>("SWM.Logging", 1, 0, "LogListModel");
    qmlRegisterType<swm::runtime::tasks::TaskListModel>("SWM.Tasks", 1, 0, "TaskListModel");

    qmlEngine.rootContext()->setContextProperty("logStats", stats.get());

    auto notifStats = std::any_cast<std::shared_ptr<swm::runtime::notifications::NotificationStatistics>>(registry.resolve("NotificationStatistics"));
    qmlEngine.rootContext()->setContextProperty("RuntimeNotificationStats", notifStats.get());

    auto notifListModel = std::any_cast<std::shared_ptr<swm::runtime::notifications::NotificationListModel>>(registry.resolve("NotificationListModel"));
    qmlEngine.rootContext()->setContextProperty("RuntimeNotificationList", notifListModel.get());

    qmlEngine.rootContext()->setContextProperty("logExport", logExport);
    
    qmlEngine.rootContext()->setContextProperty("taskStats", taskStats.get());
    qmlEngine.rootContext()->setContextProperty("taskListModel", taskListModel.get());

    logger->info("Application Started", LogCategory::Runtime);
    logger->info("Runtime Initialized", LogCategory::Runtime);
    logger->info("Logger Ready", LogCategory::Runtime);
    logger->info("Configuration Loaded", LogCategory::Runtime);
    logger->info("UI Started", LogCategory::Runtime);

    QString appDir = QCoreApplication::applicationDirPath();
    qmlEngine.addImportPath(appDir + "/../ui");
    qmlEngine.rootContext()->setContextProperty("bootstrap", this);
    qmlEngine.load(QUrl::fromLocalFile(appDir + "/../ui/playground/PlaygroundApp.qml"));
}
