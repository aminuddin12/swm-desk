#ifndef LOGGERFACADE_H
#define LOGGERFACADE_H

#include "ILogger.h"

class LoggerFacade {
public:
    static void initialize(ILogger *loggerInstance);
    static ILogger* get();
private:
    static ILogger *activeLogger;
};

#endif
