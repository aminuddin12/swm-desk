# Design System Specification

## 1. UI Philosophy & Core Characteristics
SWM Desk dibangun dengan nilai-nilai desain:
- **Desktop First**: UX dan interaction model memprioritaskan mouse, keyboard, dan shortcut.
- **Card Based & Content First**: Informasi dipisahkan menggunakan kartu-kartu elevasi dengan ruang kosong (spacious) yang cukup.
- **Premium & Native Feel**: Smooth, responsif terhadap OS, minim border tebal, menggunakan soft shadow dan micro-animations.

## 2. Foundation Layer
Berisi konstanta absolut primitif.
- **Colors**: Palet murni (Blue 50-900, Gray 50-900, dll.).
- **Typography**: Skala (H1-H6, Body, Caption), Ketebalan (Regular, Medium, SemiBold, Bold).
- **Spacing**: `4`, `8`, `12`, `16`, `20`, `24`, `32`, `40`, `48`, `64`.
- **Shapes / Radius**: `6`, `10`, `14`, `18`, `24`.
- **Elevation**: Skala shadow 1 hingga 5 (untuk Card, Dropdown, Dialog).

## 3. Theme Engine
Sistem bertugas memetakan primitif dari Foundation ke dalam variabel semantik untuk Component.
- **Warna Semantik**: `background`, `surface`, `primary`, `success`, `warning`, `error`, `textPrimary`, `textSecondary`, `border`.
- **Mode yang Didukung (Future-Ready)**: System, Light, Dark, OLED (True Black), High Contrast, Custom, Marketplace.

## 4. Accent Engine
- Menyediakan pergantian warna "brand" tanpa mengganti tema.
- Pilihan: Blue, Purple, Orange, Green, Red, Pink, Teal.
- Komponen menggunakan `Theme.accent` yang dikendalikan oleh Accent Engine.

## 5. Motion System
- Memisahkan definisi dari sekadar durasi. Motion dipetakan dalam tipe:
  - `Fade` (Opacity interpolation)
  - `Slide` (Position X/Y displacement)
  - `Scale` (Transform scale)
  - `Elevation` (Z-Index / Shadow transition)
- **Token Durasi**: Hover/Tap (150ms), Navigation (220ms), Dialog (250ms), Page (280ms).
- Mendukung fitur *Reduced Motion* untuk seketika memotong animasi demi aksebilitas.

## 6. Resources & Asset Management
Folder `resources/` ditempatkan terpisah di luar `ui/`.
- **Font**: Menanamkan `Inter-VariableFont.ttf`.
- **Fallback OS**: macOS (SF Pro), Windows (Segoe UI Variable), Linux (Inter).
- **Icon**: Semua ikon berasal dari Lucide / Tabler berformat SVG, dirender menggunakan custom `SWMIcon` tanpa pemuatan `Image` rasio mentah.
