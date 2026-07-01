# Module System

SWM Desk features a dynamic Module System to keep application components segregated.

## Specifications

- Each feature is declared inside the `modules/` folder as a self-contained unit.
- A feature module implements the `IModule` C++ interface:
  - `initialize()`: Sets up SQLite tables or registers routes.
  - `shutdown()`: Cleans up memory, file handles, or network sockets.
- The `ModuleManager` resolves registered modules dynamically during bootstrap and exposes their ViewModels to the presentation layer.
