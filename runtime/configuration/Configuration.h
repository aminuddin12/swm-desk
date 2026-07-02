#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../../core/contracts/IConfiguration.h"

class Configuration : public IConfiguration {
public:
    Configuration();
    ~Configuration() override;

    LoggingConfig getLoggingConfig() const override;
    RuntimeConfig getRuntimeConfig() const override;
    UiConfig getUiConfig() const override;
    ThemeConfig getThemeConfig() const override;
};

#endif
