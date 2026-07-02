#include "Configuration.h"

Configuration::Configuration() {
}

Configuration::~Configuration() {
}

LoggingConfig Configuration::getLoggingConfig() const {
    return LoggingConfig{2000, 500, 50, 7};
}

RuntimeConfig Configuration::getRuntimeConfig() const {
    return RuntimeConfig{"Development"};
}

UiConfig Configuration::getUiConfig() const {
    return UiConfig{"Light"};
}

ThemeConfig Configuration::getThemeConfig() const {
    return ThemeConfig{"Green"};
}
