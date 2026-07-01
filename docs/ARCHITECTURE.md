# Architecture Overview

SWM Desk is built using a strict Clean Architecture pattern. The system is split into independent rings of responsibility, where dependencies only flow inwards.

## Layer Definitions

1. **Presentation Layer (Outermost)**: Includes QML UI, widgets, and C++ ViewModels. It delegates actions to the Application layer.
2. **Application Layer**: Contains facades, command handlers, and orchestrators (like `AppBootstrap` and `ModuleManager`).
3. **Core Layer (Innermost)**: Houses core engine logic (renderer, timeline, overlays) and interfaces/contracts. It is independent of Qt UI, databases, and servers.
4. **Infrastructure Layer**: Implements core interfaces for specific technologies (SQLite, WebSockets, Local File System).

This design ensures the Core engine can be compiled and verified independently of UI changes.
