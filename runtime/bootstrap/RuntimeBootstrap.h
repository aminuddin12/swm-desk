#ifndef RUNTIMEBOOTSTRAP_H
#define RUNTIMEBOOTSTRAP_H

#include "RuntimeContext.h"
#include <memory>

class RuntimeBootstrap {
public:
    static std::shared_ptr<RuntimeContext> bootstrap();
};

#endif
