#ifndef IEVENTBUS_H
#define IEVENTBUS_H

#include <string>
#include <functional>

class IEventBus {
public:
    virtual ~IEventBus() = default;
    virtual void publish(const std::string &event, const std::string &payload) = 0;
    virtual void subscribe(const std::string &event, std::functional<void(const std::string&)> callback) = 0;
};

#endif
