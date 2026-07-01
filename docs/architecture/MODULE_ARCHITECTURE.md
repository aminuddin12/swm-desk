# Module Architecture Specification

## 1. Everything is a Module
Dalam filosofi SWM Desk, tidak ada fitur sentralistis. Semua fitur utama wajib dikapsulasi sebagai Module, termasuk:
- Dashboard
- Templates
- Marketplace
- Assets
- OBS
- Settings
- Plugin
- Teleprompter (future)
- Scoreboard (future)
- Countdown (future)
- Media Browser (future)
- Audio Manager (future)
- Camera Controller (future)

Dashboard tidak memiliki keistimewaan khusus; ia diinisialisasi dan diatur dengan siklus hidup yang sama persis seperti Teleprompter atau Settings.

## 2. The Module Contract (Interfaces)
Setiap Module harus mengimplementasikan/menyesuaikan diri pada kontrak ketat (C++ maupun QML):

- `IModule`: Antarmuka dasar implementasi modul.
- `ModuleManifest`: Deklarasi ID, Nama, dan Versi dari Modul.
- `ModuleMetadata`: Informasi author, ikon, warna aksen spesifik, dan deskripsi singkat.
- `ModuleLifecycle`: Status inisialisasi (`onLoad()`, `onEnable()`, `onDisable()`, `onUnload()`).
- `ModuleContext`: Akses terbatas Modul ke ekosistem SWM Desk (misal untuk mengambil Logger atau Service).
- `ModulePermissions`: Membatasi modul (apakah boleh mengakses API eksternal, File System, atau WebSocket).
- `ModuleEvents`: Definisi event spesifik yang dipancarkan oleh modul ini ke sistem.
- `ModuleDependencies`: Daftar spesifikasi versi Modul lain yang wajib ada agar Modul ini berjalan.
- `ModuleRegistry`: Pendaftaran sentral tempat Platform mendaftar dan mencari Modul.

Dengan infrastruktur ini, Modul baru dapat ditambah/dicopot (bahkan di tengah runtime) tanpa menghentikan Platform atau merusak UI.
