pragma Singleton
import QtQuick

QtObject {
    // SWM Foundation Primitive Colors
    // DO NOT USE DIRECTLY IN COMPONENTS. USE THEME ENGINE INSTEAD.
    
    // Grayscale
    readonly property color gray50: "#f9fafb"
    readonly property color gray100: "#f3f4f6"
    readonly property color gray200: "#e5e7eb"
    readonly property color gray300: "#d1d5db"
    readonly property color gray400: "#9ca3af"
    readonly property color gray500: "#6b7280"
    readonly property color gray600: "#4b5563"
    readonly property color gray700: "#374151"
    readonly property color gray800: "#1f2937"
    readonly property color gray900: "#111827"
    readonly property color gray950: "#030712"
    
    // Pure
    readonly property color white: "#ffffff"
    readonly property color black: "#000000"
    
    // Semantic Primitives
    readonly property color red500: "#ef4444"
    readonly property color green500: "#10b981"
    readonly property color yellow500: "#f59e0b"
    readonly property color blue500: "#3b82f6"
    readonly property color purple50: "#f3f0ff"
    readonly property color purple100: "#e0d4fc"
    readonly property color purple500: "#8b5cf6"
}
