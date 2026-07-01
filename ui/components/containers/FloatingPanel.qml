import QtQuick
import QtQuick.Effects
import foundation
import theme
import components

Item {
    id: root
    
    property int padding: SWMSpacing.space16
    default property alias content: container.data
    
    implicitWidth: container.implicitWidth + (padding * 2)
    implicitHeight: container.implicitHeight + (padding * 2)
    
    Rectangle {
        id: bgRect
        anchors.fill: parent
        color: ThemeEngine.surface
        radius: SWMRadius.radiusLg
        border.color: ThemeEngine.border
        border.width: 1
    }
    
    MultiEffect {
        source: bgRect
        anchors.fill: bgRect
        shadowEnabled: true
        shadowColor: "#2A000000" // Harder shadow for floating panel
        shadowHorizontalOffset: 0
        shadowVerticalOffset: 16
        shadowBlur: 1.0
    }
    
    Item {
        id: container
        anchors.fill: parent
        anchors.margins: root.padding
    }
}
