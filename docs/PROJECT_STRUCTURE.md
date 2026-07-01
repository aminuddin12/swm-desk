# Project Structure

Overview of the root directory layout for SWM Desk:

- **app**: Main initialization and application bootstrapper.
- **core**: The core broadcast engine containing runtime, renderer, animation, and timeline controllers.
- **presentation**: Declarative QML layouts, themes, and pages.
- **application**: Services, usecases, facades, and registry orchestration.
- **infrastructure**: Database, network socket, and logging implementations.
- **modules**: Feature-specific modules (Dashboard, Templates, Assets) containing self-contained logic and QML.
- **plugins**: Extensibility plugin loaders, registries, and dynamic libraries.
- **packages**: Extension package installers, validators, and extractors.
- **sdk**: Public API, template documentation, and examples for developer integrations.
- **shared**: Common types, enums, and constants.
