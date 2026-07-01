#include "PluginManager.h"

PluginManager& PluginManager::instance() {
    static PluginManager inst;
    return inst;
}

void PluginManager::loadPlugins() {
    for (auto &plugin : plugins) {
        plugin->onEnable();
    }
}

void PluginManager::unloadPlugins() {
    for (auto &plugin : plugins) {
        plugin->onDisable();
    }
}

void PluginManager::registerPlugin(std::shared_ptr<IPlugin> plugin) {
    plugins.push_back(plugin);
}
