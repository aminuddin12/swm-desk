# OBS Studio Plugin Integration (swmpluginlib)

Bridges the Sw-desk Tauri application with OBS Studio. It registers a custom source type named "Lower Thirds (SWM)" in OBS Studio. 

The library runs a built-in background WebSocket server on port 4500 and monitors the SWM Desk SQLite database. Any changes selected either in SWM Desk or in the OBS properties page of the source are synced automatically to the browser overlay.

## Compilation

Build the C++ library using CMake:

```bash
mkdir -p build && cd build
cmake ..
make
```

Upon successful compilation, the output file `swmpluginlib.so` will be created in the `build` directory.

## Installation

Copy the compiled library to the OBS Studio plugins directory:

```bash
cp swmpluginlib.so ~/Library/Application/Support/obs-studio/plugins/
```

## How it Works

The plugin starts a lightweight background WebSocket server on port 4500 when OBS starts. The Overlay page in the Tauri application connects to ws://localhost:4500 and receives real-time updates. When options are updated in OBS, the plugin writes directly to the SQLite settings database to sync with the application.
