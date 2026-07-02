#include "LoggerFacade.h"

ILogger* LoggerFacade::activeLogger = nullptr;

void LoggerFacade::initialize(ILogger *loggerInstance) {
    activeLogger = loggerInstance;
}

ILogger* LoggerFacade::get() {
    return activeLogger;
}
