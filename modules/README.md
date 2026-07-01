# Modules Layer

## Responsibility
Contains self-contained feature modules (Dashboard, Templates, Assets, Settings). Each module must be completely isolated and hold its own configs, services, and QML.

## Allowed Dependencies
- `core`
- `application`
- `shared`

## Forbidden Dependencies
- Inter-module concrete dependencies (use dynamic event messaging to cross boundaries)
