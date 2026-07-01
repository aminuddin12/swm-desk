# Service Architecture Specification

## 1. Separation of Concerns
SWM Desk mengelola Business Logic, IO, State, dan Network murni melalui Service Layer. Service adalah entitas tak kasat mata (headless) yang melayani fungsionalitas secara reaktif atau pasif.

- UI dilarang keras mengetahui (atau langsung menginstansiasi) implementasi Service.
- UI hanya berinteraksi melalui *Interface* (`IThemeService`, `IMarketplaceService`).

## 2. Core Platform Services
Daftar Service standar (dan service di masa depan) yang akan berjalan dalam latar belakang Platform:

- `SettingsService` (Mengelola persistensi SQLite/JSON config)
- `ThemeService` (Menyiapkan semantic colors & accent)
- `NavigationService` (State router aktif)
- `LocalizationService` (Sistem I18N multi-bahasa)
- `NotificationService` (Routing toast notification ke UI)
- `WindowService` (Manajemen window spawn/overlay)
- `DialogService` (Eksekusi blocker prompt konfirmasi)
- `OverlayService` (Mengirim data grafis/chroma ke layer luar)
- `MarketplaceService` (Fetch HTTP marketplace packages)
- `PluginService` (Resolusi dan isolasi shared library native)
- `AssetService` (Manajemen local files media)
- `OBSService` (Komunikasi ke SWM OBS Plugin via WebSocket)
- `ApiService` (Server REST API / WebSocket Server internal)
- `LoggerService` (Penulisan sink log text)
- `AnalyticsService` (Future: tracking internal actions)
- `TelemetryService` (Optional: debugging data / crashlytics)

## 3. Service Registry
Platform memegang satu `ServiceRegistry` singleton di level C++. Modul akan meminta service ke registry melalui fungsi *Dependency Injection* (DI).
