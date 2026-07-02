#include "ServiceRegistry.h"

ServiceRegistry& ServiceRegistry::instance() {
    static ServiceRegistry inst;
    return inst;
}

void ServiceRegistry::registerService(const std::string &name, std::any service) {
    services[name] = service;
}

std::any ServiceRegistry::resolve(const std::string &name) {
    auto it = services.find(name);
    if (it != services.end()) {
        return it->second;
    }
    return {};
}

bool ServiceRegistry::contains(const std::string &name) const {
    return services.find(name) != services.end();
}

void ServiceRegistry::remove(const std::string &name) {
    services.erase(name);
}
