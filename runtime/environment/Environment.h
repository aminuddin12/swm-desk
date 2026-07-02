#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "../../core/contracts/IEnvironment.h"

class Environment : public IEnvironment {
public:
    Environment();
    ~Environment() override;

    std::string getApplicationDataPath() const override;
    std::string getCachePath() const override;
    std::string getLogsPath() const override;
    std::string getPluginsPath() const override;
    std::string getAssetsPath() const override;
    std::string getTemplatesPath() const override;
    std::string getMarketplacePath() const override;
    std::string getDownloadsPath() const override;
    std::string getConfigPath() const override;
};

#endif
