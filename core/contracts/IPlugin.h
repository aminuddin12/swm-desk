#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <string>

class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual std::string pluginId() const = 0;
    virtual void onEnable() = 0;
    virtual void onDisable() = 0;
};

#endif
