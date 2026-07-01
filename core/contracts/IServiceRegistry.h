#ifndef ISERVICEREGISTRY_H
#define ISERVICEREGISTRY_H

#include <string>
#include <any>

class IServiceRegistry {
public:
    virtual ~IServiceRegistry() = default;
    virtual void registerService(const std::string &name, std::any service) = 0;
    virtual std::any getService(const std::string &name) = 0;
};

#endif
