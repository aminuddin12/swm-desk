# Theme Engine Specification

## 1. Engine Boundaries
Theme Engine bekerja independen dari Design Foundation. Komponen Theme Engine menerima Base Foundation Colors dan memanipulasinya secara selektif ke dalam variabel *Semantic Colors*.

## 2. Dynamic Modes
Theme Engine dirancang menampung mode berikut:
- **System**: Mengikuti status OS lokal pengguna.
- **Light Theme**: Mode terang elegan.
- **Dark Theme**: Mode gelap standar.
- **OLED Theme**: Mode "True Black" eksklusif (`#000000`).
- **High Contrast**: Kontras absolut tanpa gradasi demi visibilitas (Accessibility).
- **Marketplace Theme / Custom Theme**: Memungkinkan sistem me-*load* payload JSON/QML berisi penggantian variabel kustom.

## 3. Accent Engine Integration
Aksen adalah pewarna dominan untuk Primary Actions (seperti SWMButton) atau *Focus Rings*. Accent Engine sepenuhnya terpisah dari Theme Engine. 
- Saat Theme disetel "Dark" dan Accent disetel "Green", Button akan memiliki *Green Focus* pada *Dark Surface*.
- Dukungan varian: Blue, Purple, Orange, Green, Red, Pink, Teal.
