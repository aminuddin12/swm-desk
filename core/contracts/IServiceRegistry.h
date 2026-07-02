#ifndef ISERVICEREGISTRY_H
#define ISERVICEREGISTRY_H

#include <string>
#include <any>

class IServiceRegistry {
public:
    virtual ~IServiceRegistry() = default;
    virtual void registerService(const std::string &name, std::any service) = 0;
    virtual std::any resolve(const std::string &name) = 0;
    virtual bool contains(const std::string &name) const = 0;
    virtual void remove(const std::string &name) = 0;
};

#endif
