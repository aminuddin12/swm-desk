#include "WindowOverlaySink.h"

WindowOverlaySink::WindowOverlaySink() {
}

WindowOverlaySink::~WindowOverlaySink() {
}

void WindowOverlaySink::log(const LogEntry &entry) {
    (void)entry;
}

bool WindowOverlaySink::shouldLog(LogLevel level, LogCategory category) const {
    (void)level;
    (void)category;
    return false;
}

void WindowOverlaySink::flush() {
}

void WindowOverlaySink::setFormatter(std::shared_ptr<ILogFormatter> formatter) {
    (void)formatter;
}

void WindowOverlaySink::setFilters(LogLevel minLevel, const std::vector<LogCategory> &categories) {
    (void)minLevel;
    (void)categories;
}
