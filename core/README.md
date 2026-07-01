# Core Layer

## Responsibility
Contains the main broadcast graphics engine (runtime, renderer, overlay logic, variables, scheduler, animation). Exposes core contract interfaces in `core/contracts/`.

## Allowed Dependencies
- `shared`
- Standard C++ library headers

## Forbidden Dependencies
- `presentation`
- `infrastructure` (e.g. direct database, server sockets)
- `integrations` (e.g. OBS Studio API)
- Qt QML / UI components
