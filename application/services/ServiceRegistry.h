#ifndef SERVICEREGISTRY_H
#define SERVICEREGISTRY_H

#include "../../core/contracts/IServiceRegistry.h"
#include <unordered_map>

class ServiceRegistry : public IServiceRegistry {
public:
    static ServiceRegistry& instance();
    void registerService(const std::string &name, std::any service) override;
    std::any resolve(const std::string &name) override;
    bool contains(const std::string &name) const override;
    void remove(const std::string &name) override;
private:
    ServiceRegistry() = default;
    std::unordered_map<std::string, std::any> services;
};

#endif
