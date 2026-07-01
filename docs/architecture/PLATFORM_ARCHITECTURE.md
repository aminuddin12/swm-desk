# Platform Architecture Specification

## 1. Core Philosophy: Platform First
SWM Desk dirancang sebagai **Desktop Platform**, bukan sekadar aplikasi monolitik. Arsitektur dibangun berdasarkan rantai ketergantungan (Dependency Chain) yang ketat:

**Platform → Services → Modules → UI → Features**

Pusat aplikasi bukanlah UI atau Dashboard, melainkan Platform Core. UI dan Dashboard hanyalah implementasi dari infrastruktur yang mendasarinya. Desain ini memastikan platform siap menampung fitur tanpa batas selama 10+ tahun ke depan.

## 2. Abstraction & Decoupling
Seluruh bagian sistem harus sangat modular, event-driven, dan terdekapsulasi (decoupled).
- UI tidak mengetahui asal data; UI hanya mengikat (bind) diri ke *State* atau mendengarkan *EventBus*.
- MainWindow tidak mengetahui isi konten; ia hanya menyediakan *WorkspaceContainer*.
- Platform tidak mengetahui spesifikasi modul bisnis (mis. OBS, Marketplace); Platform hanya mengetahui ada entitas bertipe `IModule`.

## 3. SDK Ecosystem
Untuk memastikan ekspansi jangka panjang, SWM Desk memelihara layer SDK (Software Development Kit) secara native. Ini memungkinkan komunitas pihak ketiga atau tim internal untuk mengekstensi aplikasi tanpa memodifikasi *Core Engine*. 
Struktur SDK:
- `sdk/module-sdk/`
- `sdk/plugin-sdk/`
- `sdk/theme-sdk/`
- `sdk/template-sdk/`
- `sdk/marketplace-sdk/`

## 4. Development & Playground App
Mengembangkan komponen UI langsung di dalam aplikasi utama (Main App) dilarang.
- Setiap komponen, tema, atau layout eksperimental harus diisolasi dan diuji dalam **Playground App**.
- Playground bertindak sebagai lingkungan laboratorium yang mem-bypass Service dan Logic Core untuk mempercepat iterasi visual secara mandiri.

## 5. Development Principles
Semua iterasi kode harus patuh pada sepuluh prinsip SWM Desk:
1. **Modular**
2. **Reusable**
3. **Decoupled**
4. **Event Driven**
5. **Platform First**
6. **Desktop Native**
7. **Documentation First**
8. **Testable**
9. **Scalable**
10. **Future Proof**
