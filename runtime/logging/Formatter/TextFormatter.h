#ifndef TEXTFORMATTER_H
#define TEXTFORMATTER_H

#include "ILogFormatter.h"

class TextFormatter : public ILogFormatter {
public:
    TextFormatter();
    ~TextFormatter() override;

    std::string format(const LogEntry &entry) override;
};

#endif
