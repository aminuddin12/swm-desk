#include "RuntimeContext.h"

RuntimeContext::RuntimeContext(std::shared_ptr<IEnvironment> env,
                               std::shared_ptr<ILogger> log,
                               std::shared_ptr<IEventBus> bus)
    : environment(env), logger(log), eventBus(bus) {
}

RuntimeContext::~RuntimeContext() {
}

std::shared_ptr<IEnvironment> RuntimeContext::getEnvironment() const {
    return environment;
}

std::shared_ptr<ILogger> RuntimeContext::getLogger() const {
    return logger;
}

std::shared_ptr<IEventBus> RuntimeContext::getEventBus() const {
    return eventBus;
}
