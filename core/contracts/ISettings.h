#ifndef ISETTINGSMANAGER_H
#define ISETTINGSMANAGER_H

#include <string>

class ISettings {
public:
    virtual ~ISettings() = default;
    virtual std::string get(const std::string &key, const std::string &defaultValue = "") = 0;
    virtual void set(const std::string &key, const std::string &value) = 0;
};

#endif
