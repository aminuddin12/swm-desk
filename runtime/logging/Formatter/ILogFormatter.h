#ifndef ILOGFORMATTER_H
#define ILOGFORMATTER_H

#include "../LogEntry.h"
#include <string>

class ILogFormatter {
public:
    virtual ~ILogFormatter() = default;
    virtual std::string format(const LogEntry &entry) = 0;
};

#endif
