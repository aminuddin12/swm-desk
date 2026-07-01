# Navigation Framework Specification

## 1. Module Registry Discovery
Navigation Framework dalam SWM Desk tidak memiliki entri data statis/hardcoded (misal: "Menu 1: Dashboard, Menu 2: Template"). 

Sebagai gantinya, Navigation mengkueri `ModuleRegistry` untuk meminta `getLoadedModules()`. Setiap Modul menyertakan metadata ikon dan path. Navigation secara dinamis merender Menu *Rail* atau *Tab* berbasis data ini. Modul baru yang terdeteksi akan langsung muncul otomatis di bilah navigasi.

## 2. Omnidirectional Placement
`NavigationManager` mendukung render UI di seluruh titik:
- **Left**: Navigasi Rail/Drawer standar.
- **Right**: Berguna bagi pengguna kidal atau tata letak panel kontrol sekunder.
- **Top**: Pendekatan Tab horizontal (seperti Arc Browser Header).
- **Bottom**: Mode ringkas layaknya aplikasi Mobile.
- **Floating / Docked**: Memisahkan bar menu dari `WorkspaceContainer` menjadi floating pill.

## 3. States & Responsiveness
Navigasi memiliki properti:
- `Compact Mode`: Hanya Icon.
- `Expanded Mode`: Icon dan Label Teks.
Perubahan posisi dari `Left` (Expanded) ke `Bottom` akan memicu reflow UI secara seketika (*hot switch*) ke seluruh komponen Content/Workspace.
