#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "../../core/contracts/IPlugin.h"
#include <vector>
#include <memory>

class PluginManager {
public:
    static PluginManager& instance();
    void loadPlugins();
    void unloadPlugins();
    void registerPlugin(std::shared_ptr<IPlugin> plugin);
private:
    PluginManager() = default;
    std::vector<std::shared_ptr<IPlugin>> plugins;
};

#endif
