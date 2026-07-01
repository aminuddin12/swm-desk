# Dependency Rules

SWM Desk enforces a strict dependency direction. Violating these rules will lead to build breaks and circular compile failures.

## Permitted Flows

- **Presentation** can depend on **Application** and **Core**.
- **Application** can depend on **Core**.
- **Infrastructure** implements **Core/contracts**.
- **Modules** can depend on **Core** and **Application/facades**.

## Forbidden Flows

- **Core** MUST NOT import QML, Qt Quick, QWidget, SQLite, WebSockets, or network headers.
- **Application** MUST NOT import UI views or specific platform renderers.
- No layer can hold circular dependencies. Use interface injection (ServiceRegistry) to bypass concrete requirements.
