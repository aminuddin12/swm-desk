#include "ModuleManager.h"

ModuleManager& ModuleManager::instance() {
    static ModuleManager inst;
    return inst;
}

void ModuleManager::registerModule(std::shared_ptr<IModule> module) {
    modules.push_back(module);
}

void ModuleManager::initializeModules() {
    for (auto &module : modules) {
        module->initialize();
    }
}

void ModuleManager::shutdownModules() {
    for (auto &module : modules) {
        module->shutdown();
    }
}
