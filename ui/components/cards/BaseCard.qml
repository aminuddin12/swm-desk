import QtQuick
import QtQuick.Effects
import foundation
import theme

Item {
    id: root
    
    property int padding: SWMSpacing.space24
    property bool hoverable: false
    property color backgroundColor: ThemeEngine.surface
    
    // Allow children
    default property alias content: container.data
    
    implicitWidth: container.implicitWidth + (padding * 2)
    implicitHeight: container.implicitHeight + (padding * 2)
    
    Rectangle {
        id: bgRect
        anchors.fill: parent
        color: root.backgroundColor
        radius: SWMRadius.radius2xl
        
        border.color: ThemeEngine.border
        border.width: 1
        
        // Hover scaling effect for premium feel
        scale: (root.hoverable && mouseArea.containsMouse) ? 1.01 : 1.0
        
        Behavior on scale {
            NumberAnimation { duration: SWMMotion.durationFast; easing.type: SWMMotion.easingStandard }
        }
    }
    
    // Soft Premium Shadow
    MultiEffect {
        source: bgRect
        anchors.fill: bgRect
        shadowEnabled: ThemeEngine.mode === "Light"
        shadowColor: "#0A000000" // 4% black
        shadowHorizontalOffset: 0
        shadowVerticalOffset: (root.hoverable && mouseArea.containsMouse) ? 16 : 8
        shadowBlur: (root.hoverable && mouseArea.containsMouse) ? 0.8 : 0.4
        
        Behavior on shadowVerticalOffset { NumberAnimation { duration: SWMMotion.durationFast } }
        Behavior on shadowBlur { NumberAnimation { duration: SWMMotion.durationFast } }
    }
    
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: root.hoverable
        cursorShape: root.hoverable ? Qt.PointingHandCursor : Qt.ArrowCursor
        acceptedButtons: Qt.NoButton
    }
    
    Item {
        id: container
        anchors.fill: parent
        anchors.margins: root.padding
    }
}
