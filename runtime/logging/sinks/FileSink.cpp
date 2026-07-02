#include "FileSink.h"
#include <iostream>
#include <algorithm>
#include <QDir>

FileSink::FileSink(const std::string &logsDirectory) : logsDir(logsDirectory) {
}

FileSink::~FileSink() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

void FileSink::openFile(const std::string &dateStr) {
    if (fileStream.is_open()) {
        if (currentFileDate == dateStr) {
            return;
        }
        fileStream.close();
    }

    currentFileDate = dateStr;
    std::string filePath = logsDir + "/" + dateStr + ".log";
    
    QDir().mkpath(QString::fromStdString(logsDir));
    
    fileStream.open(filePath, std::ios::out | std::ios::app);
    if (!fileStream) {
        isActive = false;
        retryCounter = 100;
        std::cerr << "FileSink failed to open file: " << filePath << std::endl;
    } else {
        isActive = true;
    }
}

void FileSink::log(const LogEntry &entry) {
    std::lock_guard<std::mutex> lock(sinkMutex);
    
    if (!isActive) {
        if (retryCounter > 0) {
            --retryCounter;
            return;
        }
    }

    std::string dateStr = entry.timestamp.substr(0, 10);
    openFile(dateStr);

    if (!isActive || !fileStream.is_open()) {
        return;
    }

    if (logFormatter) {
        std::string formatted = logFormatter->format(entry);
        fileStream << formatted << "\n";
        if (fileStream.fail()) {
            isActive = false;
            retryCounter = 100;
            std::cerr << "FileSink write failed." << std::endl;
        }
    }
}

bool FileSink::shouldLog(LogLevel level, LogCategory category) const {
    if (static_cast<int>(level) < static_cast<int>(minimumLevel)) {
        return false;
    }
    if (allowedCategories.empty()) {
        return true;
    }
    return std::find(allowedCategories.begin(), allowedCategories.end(), category) != allowedCategories.end();
}

void FileSink::flush() {
    std::lock_guard<std::mutex> lock(sinkMutex);
    if (isActive && fileStream.is_open()) {
        fileStream.flush();
    }
}

void FileSink::setFormatter(std::shared_ptr<ILogFormatter> formatter) {
    std::lock_guard<std::mutex> lock(sinkMutex);
    logFormatter = formatter;
}

void FileSink::setFilters(LogLevel minLevel, const std::vector<LogCategory> &categories) {
    std::lock_guard<std::mutex> lock(sinkMutex);
    minimumLevel = minLevel;
    allowedCategories = categories;
}
