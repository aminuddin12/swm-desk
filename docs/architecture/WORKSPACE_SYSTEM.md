# Workspace System Specification

## 1. Minimal Window Root
Aplikasi utama (`MainWindow.qml`) adalah container polos. Tidak ada hardcode elemen khusus atau fitur di root. Root memisahkan lapisan layar ke dalam:
- `TitleBar`
- `WorkspaceContainer` (Container Navigasi + Konten)
- `OverlayContainer`
- `DialogContainer`
- `ToastContainer`
- `FloatingPanelContainer`
- `StatusBar`

## 2. Workspace Container Isolation
Di dalam SWM Desk, UI tidak membungkus "Dashboard". MainWindow membungkus **WorkspaceContainer**. WorkspaceContainer berfungsi sebagai grid host yang direntangkan ke sekeliling window, menyisakan area untuk Navigation.

Setiap saat, Modul (seperti Dashboard, Marketplace, atau Teleprompter) akan dilempar ke (injected into) `WorkspaceContainer`. MainWindow tidak mengetahui jenis atau ID spesifik modul yang saat ini sedang aktif (Blind Host). Hal ini memutus tight-coupling antara Core UI dan Business Module.
