#ifndef TYPES_H
#define TYPES_H

#include <string>

namespace Shared {
    struct ServiceStatus {
        std::string name;
        bool isOnline;
    };
}

#endif
