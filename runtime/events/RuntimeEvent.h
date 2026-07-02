#ifndef RUNTIMEEVENT_H
#define RUNTIMEEVENT_H

enum class RuntimeEvent {
    LogAdded,
    ClearMemoryLogs,
    MemoryLogsCleared,
    WindowRequest,
    ReloadUI,
    TaskChanged,
    NotificationChanged
};

#endif
