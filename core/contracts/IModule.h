#ifndef IMODULE_H
#define IMODULE_H

#include <string>

class IModule {
public:
    virtual ~IModule() = default;
    virtual std::string name() const = 0;
    virtual void initialize() = 0;
    virtual void shutdown() = 0;
};

#endif
