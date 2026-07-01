# Component Catalog

## 1. Organisasi Komponen (SWM.Components)

Komponen tidak lagi dipisah sebatas jenisnya (seperti `buttons/`), tetapi dikelompokkan secara semantik ke dalam hierarki yang lebih modular:

- `base/` (Komponen inti terkecil: Icon, Typography, Divider)
- `display/` (Komponen penampil: Badge, Avatar, Chip, Tooltip, Skeleton)
- `navigation/` (Elemen navigasi: TopBar, BottomBar, Rail, Breadcrumb, Tab)
- `feedback/` (Notifikasi ke user: Toast, Dialog, Modal, Progress)
- `forms/` (Input elemen: TextField, SearchBar, Checkbox, Switch, Slider)
- `layout/` (Pembungkus terstruktur: ScrollArea, GridView)
- `overlay/` (Elemen mengambang: Dropdown, ContextMenu, Popover)
- `containers/` (Block UI yang lebih besar: Card, SWMStatusCard, dll.)

## 2. Standar Component States
Semua komponen Interaktif (Buttons, Inputs, Cards, Navigation) WAJIB merespons dan mendeklarasikan state QML berikut:
- **Normal**: State statis default.
- **Hover**: Cursor mouse berada di atas elemen (mengaktifkan *Hover Animation* / *Elevation*).
- **Pressed**: Elemen sedang diklik (mengaktifkan *Ripple* / *Scale Down*).
- **Focused**: Tab navigation menyoroti elemen (mengaktifkan *Focus Ring* untuk A11y).
- **Disabled**: Status tak dapat berinteraksi (mengurangi opacity, cursor disabled, menonaktifkan klik).
- **Loading / Active / Error / Success**: State fungsional kontekstual.

## 3. Daftar Spesifikasi Komponen (SWM Component List)

| Kategori | Nama Komponen | Deskripsi & Spesifikasi |
|---|---|---|
| **Base** | `SWMIcon` | Render path SVG secara dinamis; mendukung Theme Colors & Size Tokens. |
| **Base** | `SWMTypography`| Label teks pintar yang langsung mengaplikasikan font "Inter" dan ukuran standar. |
| **Forms** | `SWMButton` | Varian: Primary, Secondary, Ghost, Outline, Danger. Mendukung state *Loading* & *Disabled*. |
| **Forms** | `SWMInput` | Single-line / Multi-line input dengan properti error, success, clear button, dan label animasi. |
| **Forms** | `SWMSearchBar`| Input spesifik pencarian (dengan ikon *magnifier* & debounce logic untuk UI event). |
| **Display**| `SWMBadge` | Indikator kecil (Notification dot, jumlah item, "New"). |
| **Display**| `SWMAvatar` | Representasi profil dengan varian Circle / Rounded Rectangle. |
| **Display**| `SWMChip` | Tag yang dapat diklik/dihapus (digunakan di filter atau marketplace tags). |
| **Display**| `SWMSkeleton`| Placeholder loader saat loading async untuk *smooth UX*. |
| **Feedback**| `SWMProgress`| Linear dan Circular progress bar. |
| **Feedback**| `SWMToast` | Alert non-blocking di pojok layar (Success, Info, Error, Warning). |
| **Feedback**| `SWMDialog` | Interaksi level-2 blocking; konfirmasi dan input sederhana. |
| **Feedback**| `SWMModal` | Jendela besar pop-up berisi form atau setting ekstensif. |
| **Overlay**| `SWMTooltip` | Teks penjelasan (*hint*) saat hover elemen, responsif posisi. |
| **Containers**| `SWMCard` | Fondasi kotak interaktif (Elevation, Radius, Focus Ring). Varian: Normal, Hover, Selected. |
| **Containers**| `SWMStatusCard`| Menggabungkan Card + Icon + Status Text (contoh: OBS Offline). |
| **Containers**| `SWMQuickActionCard`| Menggabungkan Card + Icon besar untuk dashboard shortcuts. |
| **Containers**| `SWMTemplateCard` | Menampilkan thumbnail template grafis, judul, dan status (*Installed/Update*). |
| **Containers**| `SWMAssetCard` | Menampilkan pratinjau aset lokal (gambar/video) dengan metadata. |
| **Containers**| `SWMMarketplaceCard`| Template Card khusus dengan tombol beli/download & badge harga. |

## 4. Persyaratan Dokumentasi (Per Komponen)
Tiap folder/file komponen harus memiliki:
1. `[NamaKomponen].qml`: Source code utama.
2. `README.md`: Cara menggunakan komponen dan propertinya.
3. Contoh implementasi (`Example.qml` atau dimasukkan ke dalam **Playground Gallery**).
