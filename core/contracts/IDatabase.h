#ifndef IDATABASE_H
#define IDATABASE_H

#include <string>

class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual bool open(const std::string &path) = 0;
    virtual void close() = 0;
    virtual bool execute(const std::string &query) = 0;
};

#endif
