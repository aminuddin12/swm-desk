#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "../../core/contracts/IModule.h"
#include <vector>
#include <memory>

class ModuleManager {
public:
    static ModuleManager& instance();
    void registerModule(std::shared_ptr<IModule> module);
    void initializeModules();
    void shutdownModules();
private:
    ModuleManager() = default;
    std::vector<std::shared_ptr<IModule>> modules;
};

#endif
