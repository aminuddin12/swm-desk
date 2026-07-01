#include "ServiceRegistry.h"

ServiceRegistry& ServiceRegistry::instance() {
    static ServiceRegistry inst;
    return inst;
}

void ServiceRegistry::registerService(const std::string &name, std::any service) {
    services[name] = service;
}

std::any ServiceRegistry::getService(const std::string &name) {
    auto it = services.find(name);
    if (it != services.end()) {
        return it->second;
    }
    return {};
}
