import QtQuick
import foundation
import theme

Rectangle {
    id: root
    
    property string text: "Badge"
    property string variant: "primary" // "primary", "secondary", "success", "warning", "error"
    
    implicitWidth: badgeText.implicitWidth + (SWMSpacing.space8 * 2)
    implicitHeight: 24
    
    radius: SWMRadius.radiusFull
    color: {
        if (variant === "success") return Qt.rgba(ThemeEngine.success.r, ThemeEngine.success.g, ThemeEngine.success.b, 0.1)
        if (variant === "warning") return Qt.rgba(ThemeEngine.warning.r, ThemeEngine.warning.g, ThemeEngine.warning.b, 0.1)
        if (variant === "error") return Qt.rgba(ThemeEngine.error.r, ThemeEngine.error.g, ThemeEngine.error.b, 0.1)
        if (variant === "secondary") return ThemeEngine.divider
        return ThemeEngine.primaryLight
    }
    
    Text {
        id: badgeText
        anchors.centerIn: parent
        text: root.text
        font.family: SWMTypography.family
        font.pixelSize: SWMTypography.caption
        font.weight: SWMTypography.weightBold
        color: {
            if (variant === "success") return ThemeEngine.success
            if (variant === "warning") return ThemeEngine.warning
            if (variant === "error") return ThemeEngine.error
            if (variant === "secondary") return ThemeEngine.textSecondary
            return ThemeEngine.primary
        }
    }
}
