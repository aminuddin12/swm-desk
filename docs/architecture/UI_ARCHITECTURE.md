# UI Architecture Specification

## 1. Overview
SWM Desk dirancang sebagai **Desktop Platform** berskala komersial (setara Arc Browser, CleanMyMac X, Apple Music). UI bukan sekadar dashboard, melainkan sebuah platform grafis dinamis yang sangat modular, adaptif, dan responsif. 

## 2. Layered Architecture (Dependency Rule)
Arsitektur UI dipisahkan secara ketat (strict boundaries) menjadi lapisan (layer) satu arah:

```text
Foundation 
  ↓ 
Theme Engine / Accent Engine / Motion Engine
  ↓ 
Component Library
  ↓ 
Layout Framework / Navigation Framework
  ↓ 
Window System
  ↓ 
Feature Modules (Pages)
```
- **Foundation** murni berisi nilai primitif dan token konstan. Tidak boleh bergantung pada apa pun.
- **Theme/Accent Engine** membaca dari Foundation dan menghasilkan nilai kontekstual.
- **Component Library** mengimpor Theme & Foundation untuk rendering komponen. Komponen tidak boleh memiliki business logic.

## 3. Directory Structure
```text
ui/
  ├── foundation/       # Nilai primitif absolut (Shapes, Spacing, dsb.)
  ├── theme/            # Theme Engine & Accent Engine
  ├── components/       # Kategori komponen (base, display, forms, dsb.)
  ├── layouts/          # Susunan responsif untuk berbagai resolusi
  ├── windows/          # Pemisahan area layer (TitleBar, Content, Overlay)
  ├── navigation/       # NavigationManager (Left, Right, Top, Bottom)
  ├── pages/            # Halaman konten yang disuntikkan ke ContentContainer
  ├── playground/       # Standalone app untuk Component Gallery
  ├── animations/       # Core animation presets (Motion Framework)
  ├── shared/           # Helper scripts & QML utils
  └── styles/           # Styling murni spesifik
```

## 4. Window Framework
Main Window SWM Desk tidak memiliki layout tunggal monolitik. Layar dibagi menjadi beberapa kontainer berdasar Z-Index dan hirarki tanggung jawab:
1. **MainWindow**: Root window OS-level (berisi borderless/native window logic).
2. **TitleBar**: Native title bar custom (dengan Traffic Light untuk macOS, atau Window Controls untuk Windows).
3. **WorkspaceContainer**: Area utama yang membagi konten dan navigasi.
4. **NavigationContainer**: Menyimpan navigasi dinamis (diatur oleh NavigationManager).
5. **ContentContainer**: Area transisi halaman.
6. **OverlayContainer**: Area overlay level-1.
7. **DialogContainer**: Dialog level-2 (memblokir overlay di bawahnya).
8. **ToastContainer**: Area non-blocking untuk notifikasi.
9. **FloatingPanelContainer**: Untuk popup panel independen.

## 5. Navigation Framework
`NavigationManager` adalah engine yang independen. Halaman (Pages) tidak mengetahui di mana navigasi berada.
- **Posisi Didukung**: Left, Right, Top, Bottom, Floating, Docked.
- Perubahan orientasi mengubah tata letak secara dinamis berkat QML States.

## 6. Accessibility & Development Standards
- **A11y**: Siap mendukung Keyboard Navigation (Tab), High Contrast, Reduced Motion, Screen Reader, UI Scaling.
- **Docs**: Setiap komponen dan layer WAJIB memiliki `README.md` dan halaman demo independen di `Playground`.
