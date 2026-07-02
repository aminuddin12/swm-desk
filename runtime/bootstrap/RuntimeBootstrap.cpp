#include "RuntimeBootstrap.h"
#include "../configuration/Configuration.h"
#include "../environment/Environment.h"
#include "../events/EventBus.h"
#include "../logging/Logger.h"
#include "../logging/LoggerFacade.h"
#include "../logging/LogRepository.h"
#include "../logging/LogStatistics.h"
#include "WindowManager.h"
#include "../../application/services/ServiceRegistry.h"
#if defined(Q_OS_MAC)
#include "../logging/sinks/MacStatusBarService.h"
#endif
#include "../tasks/TaskRepository.h"
#include "../tasks/TaskService.h"
#include "../tasks/TaskStatistics.h"
#include "../tasks/TaskListModel.h"
#include "../notifications/NotificationRepository.h"
#include "../notifications/NotificationService.h"
#include "../notifications/NotificationStatistics.h"
#include "../notifications/NotificationListModel.h"
#if SWM_ENABLE_RUNTIME_DIAGNOSTICS
#include "../diagnostics/RuntimeDiagnostics.h"
#endif

std::shared_ptr<RuntimeContext> RuntimeBootstrap::bootstrap() {
    std::shared_ptr<IConfiguration> config = std::make_shared<Configuration>();
    std::shared_ptr<IEnvironment> env = std::make_shared<Environment>();
    
    auto &registry = ServiceRegistry::instance();
    registry.registerService("IConfiguration", config);
    registry.registerService("IEnvironment", env);
    
    std::shared_ptr<IEventBus> bus = std::make_shared<EventBus>();
    registry.registerService("IEventBus", bus);
    
    auto repo = std::make_shared<LogRepository>(bus);
    registry.registerService("LogRepository", repo);
    repo->initialize();
    repo->start();
    
    auto stats = std::make_shared<LogStatistics>(bus);
    registry.registerService("LogStatistics", stats);
    stats->initialize();
    stats->start();
    
    auto winMgr = std::make_shared<WindowManager>(bus);
    registry.registerService("WindowManager", winMgr);
    winMgr->initialize();
    winMgr->start();
    
    auto loggerInstance = std::make_shared<Logger>(config->getLoggingConfig());
    std::shared_ptr<ILogger> logger = loggerInstance;
    registry.registerService("ILogger", logger);
    
    LoggerFacade::initialize(logger.get());
    
    loggerInstance->initialize();
    loggerInstance->start();
    
#if defined(Q_OS_MAC)
    auto statusBar = std::make_shared<MacStatusBarService>(bus);
    registry.registerService("MacStatusBarService", statusBar);
    statusBar->initialize();
    statusBar->start();
#endif
    
    auto context = std::make_shared<RuntimeContext>(env, logger, bus);
    registry.registerService("RuntimeContext", context);
    
    // Register Task Center Services
    auto taskRepo = std::make_shared<swm::runtime::tasks::TaskRepository>();
    registry.registerService("TaskRepository", taskRepo);
    
    auto taskService = std::make_shared<swm::runtime::tasks::TaskService>(taskRepo, bus);
    registry.registerService("TaskService", taskService);
    
    auto taskStats = std::make_shared<swm::runtime::tasks::TaskStatistics>(taskRepo, bus);
    registry.registerService("TaskStatistics", taskStats);
    
    auto taskListModel = std::make_shared<swm::runtime::tasks::TaskListModel>(taskRepo, bus);
    registry.registerService("TaskListModel", taskListModel);

    // Register Notification Center Services
    auto notifRepo = std::make_shared<swm::runtime::notifications::NotificationRepository>();
    registry.registerService("NotificationRepository", notifRepo);

    auto notifService = std::make_shared<swm::runtime::notifications::NotificationService>(notifRepo, bus);
    registry.registerService("NotificationService", notifService);

    auto notifStats = std::make_shared<swm::runtime::notifications::NotificationStatistics>(bus);
    registry.registerService("NotificationStatistics", notifStats);
    notifStats->initialize();

    auto notifListModel = std::make_shared<swm::runtime::notifications::NotificationListModel>(bus);
    registry.registerService("NotificationListModel", notifListModel);
    notifListModel->initialize();

#if SWM_ENABLE_RUNTIME_DIAGNOSTICS
    auto diagnostics = std::make_shared<swm::runtime::diagnostics::RuntimeDiagnostics>(
        logger, bus, taskService, taskRepo, notifService, notifRepo
    );
    registry.registerService("RuntimeDiagnostics", diagnostics);
    diagnostics->initialize();
    diagnostics->start();
#endif
    
    return context;
}
