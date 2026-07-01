# Plugin System

SWM Desk supports community plugins via a dynamic plugin loader.

## Specifications

- Plugins are compiled as shared dynamic libraries (`.dylib` on macOS, `.dll` on Windows, `.so` on Linux).
- A plugin must implement the C++ entry interface defined in the SDK.
- The `PluginLoader` checks signatures, validates security keys, and registers hooks with the core rendering engine.
- Integrations like OBS Studio or Stream Deck are loaded as modular plugins using this system.
