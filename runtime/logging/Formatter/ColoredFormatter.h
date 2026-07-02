#ifndef COLOREDFORMATTER_H
#define COLOREDFORMATTER_H

#include "ILogFormatter.h"

class ColoredFormatter : public ILogFormatter {
public:
    ColoredFormatter();
    ~ColoredFormatter() override;

    std::string format(const LogEntry &entry) override;
};

#endif
