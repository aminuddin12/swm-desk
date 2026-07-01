# Event System Specification

## 1. Event Bus Pattern
Alih-alih saling memanggil reference fungsi antara komponen (misal: `Dashboard.updateNetwork()`), SWM Desk sepenuhnya beralih ke paradigma UI berbasis *Event-Driven*. Seluruh Platform dan UI disambungkan oleh **Event Bus**.

Komponen merespons peristiwa dunia maya, bukan mengeksekusi secara imperatif.

## 2. Core Events
Beberapa kategori Event dasar yang akan disirkulasikan dalam bus:

- `ThemeChanged`: Dipancarkan ketika user berpindah ke Dark Mode; Component akan me-*repaint* dirinya.
- `AccentChanged`: Dipancarkan saat brand color diganti.
- `ModuleLoaded` & `ModuleUnloaded`: Dipancarkan saat ada fitur dinamis siap (menginstruksikan Navigation untuk menambah menu secara otomatis).
- `NavigationChanged`: Memicu ContentContainer untuk menyuntikkan (swap) komponen QML aktif.
- `SettingsChanged`: Memicu sinkronisasi persistensi disk/UI.
- `LanguageChanged`: Memicu pemanggilan fungsi `.qsTr()` / lokalisasi ulang seketika.
- `OBSConnected` / `OBSDisconnected`: Membuka akses interaktif di modul remote OBS.
- `MarketplaceConnected`: Memberitahu sistem bahwa server online dan siap me-*refresh* feed.

## 3. Asynchronous Nature
Semua pengiriman Event ke UI berjalan *asynchronous*, membebaskan *Main Thread* agar 60fps/120fps render tidak pernah terhambat oleh operasi logic berat.
