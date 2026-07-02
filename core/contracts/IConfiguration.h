#ifndef ICONFIGURATION_H
#define ICONFIGURATION_H

#include <string>

struct LoggingConfig {
    int bufferSize;
    int flushIntervalMs;
    int flushLogCount;
    int retentionDays;
};

struct RuntimeConfig {
    std::string mode;
};

struct UiConfig {
    std::string theme;
};

struct ThemeConfig {
    std::string accent;
};

class IConfiguration {
public:
    virtual ~IConfiguration() = default;
    virtual LoggingConfig getLoggingConfig() const = 0;
    virtual RuntimeConfig getRuntimeConfig() const = 0;
    virtual UiConfig getUiConfig() const = 0;
    virtual ThemeConfig getThemeConfig() const = 0;
};

#endif
