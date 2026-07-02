#ifndef WINDOWOVERLAYSINK_H
#define WINDOWOVERLAYSINK_H

#include "ILogSink.h"

class WindowOverlaySink : public ILogSink {
public:
    WindowOverlaySink();
    ~WindowOverlaySink() override;

    void log(const LogEntry &entry) override;
    bool shouldLog(LogLevel level, LogCategory category) const override;
    void flush() override;
    void setFormatter(std::shared_ptr<ILogFormatter> formatter) override;
    void setFilters(LogLevel minLevel, const std::vector<LogCategory> &categories) override;
};

#endif
