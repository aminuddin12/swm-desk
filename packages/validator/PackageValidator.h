#ifndef PACKAGEVALIDATOR_H
#define PACKAGEVALIDATOR_H

#include <string>

class PackageValidator {
public:
    PackageValidator() = default;
    ~PackageValidator() = default;
    bool validatePackage(const std::string &packagePath);
};

#endif
