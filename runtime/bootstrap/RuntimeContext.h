#ifndef RUNTIMECONTEXT_H
#define RUNTIMECONTEXT_H

#include <memory>
#include "../../core/contracts/IEnvironment.h"
#include "../logging/ILogger.h"
#include "../../core/contracts/IEventBus.h"

class RuntimeContext {
public:
    RuntimeContext(std::shared_ptr<IEnvironment> env,
                   std::shared_ptr<ILogger> log,
                   std::shared_ptr<IEventBus> bus);
    ~RuntimeContext();

    std::shared_ptr<IEnvironment> getEnvironment() const;
    std::shared_ptr<ILogger> getLogger() const;
    std::shared_ptr<IEventBus> getEventBus() const;

private:
    std::shared_ptr<IEnvironment> environment;
    std::shared_ptr<ILogger> logger;
    std::shared_ptr<IEventBus> eventBus;
};

#endif
