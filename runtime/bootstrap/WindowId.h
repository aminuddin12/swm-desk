#ifndef WINDOWID_H
#define WINDOWID_H

enum class WindowId {
    Dashboard,
    LogViewer,
    Settings,
    About,
    GraphicsPreview
};

enum class WindowAction {
    Show,
    Hide,
    Toggle,
    Focus
};

struct WindowCommand {
    WindowId id;
    WindowAction action;
};

#endif
