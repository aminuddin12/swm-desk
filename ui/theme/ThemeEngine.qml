pragma Singleton
import QtQuick
import foundation

QtObject {
    id: root
    
    // Modes: "System", "Light", "Dark", "OLED"
    property string mode: "Light"
    
    readonly property bool isDark: mode === "Dark" || mode === "OLED"
    
    // Semantic Colors
    readonly property color background: isDark ? SWMColors.gray900 : SWMColors.purple50
    readonly property color surface: isDark ? SWMColors.gray800 : SWMColors.white
    
    readonly property color textPrimary: isDark ? SWMColors.white : SWMColors.gray900
    readonly property color textSecondary: isDark ? SWMColors.gray400 : SWMColors.gray500
    readonly property color textTertiary: isDark ? SWMColors.gray500 : SWMColors.gray400
    
    readonly property color border: isDark ? SWMColors.gray700 : SWMColors.gray200
    readonly property color divider: isDark ? SWMColors.gray800 : SWMColors.gray100
    
    readonly property color primary: AccentEngine.primary
    readonly property color primaryLight: AccentEngine.primaryLight
    readonly property color success: SWMColors.green500
    readonly property color warning: SWMColors.yellow500
    readonly property color error: SWMColors.red500
}
