#include "PackageValidator.h"

bool PackageValidator::validatePackage(const std::string &packagePath) {
    if (packagePath.empty()) {
        return false;
    }
    return true;
}
