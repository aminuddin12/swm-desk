#ifndef IENVIRONMENT_H
#define IENVIRONMENT_H

#include <string>

class IEnvironment {
public:
    virtual ~IEnvironment() = default;
    virtual std::string getApplicationDataPath() const = 0;
    virtual std::string getCachePath() const = 0;
    virtual std::string getLogsPath() const = 0;
    virtual std::string getPluginsPath() const = 0;
    virtual std::string getAssetsPath() const = 0;
    virtual std::string getTemplatesPath() const = 0;
    virtual std::string getMarketplacePath() const = 0;
    virtual std::string getDownloadsPath() const = 0;
    virtual std::string getConfigPath() const = 0;
};

#endif
