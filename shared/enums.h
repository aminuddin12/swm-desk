#ifndef ENUMS_H
#define ENUMS_H

namespace Shared {
    enum class ConnectionState {
        Offline,
        Warning,
        Online
    };

    enum class ModuleState {
        Uninitialized,
        Initializing,
        Ready,
        Failed
    };
}

#endif
