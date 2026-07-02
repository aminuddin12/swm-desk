#include "RuntimeBootstrap.h"
#include "../configuration/Configuration.h"
#include "../environment/Environment.h"
#include "../events/EventBus.h"
#include "../logging/Logger.h"
#include "../logging/LoggerFacade.h"
#include "../../application/services/ServiceRegistry.h"
#if defined(Q_OS_MAC)
#include "../logging/sinks/MacStatusBarService.h"
#endif

std::shared_ptr<RuntimeContext> RuntimeBootstrap::bootstrap() {
    std::shared_ptr<IConfiguration> config = std::make_shared<Configuration>();
    std::shared_ptr<IEnvironment> env = std::make_shared<Environment>();
    
    auto &registry = ServiceRegistry::instance();
    registry.registerService("IConfiguration", config);
    registry.registerService("IEnvironment", env);
    
    std::shared_ptr<IEventBus> bus = std::make_shared<EventBus>();
    registry.registerService("IEventBus", bus);
    
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
    
    return context;
}
