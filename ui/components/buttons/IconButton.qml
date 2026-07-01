import QtQuick
import foundation
import theme
import components

Item {
    id: root
    
    property string iconSource: ""
    property bool ghost: false
    
    implicitWidth: 40
    implicitHeight: 40
    
    Rectangle {
        id: bg
        anchors.fill: parent
        radius: SWMRadius.radiusFull
        color: {
            if (mouseArea.pressed) return ThemeEngine.divider
            if (mouseArea.containsMouse) return root.ghost ? ThemeEngine.divider : ThemeEngine.surface
            return root.ghost ? "transparent" : ThemeEngine.surface
        }
        
        border.color: (!root.ghost && ThemeEngine.mode === "Light") ? ThemeEngine.border : "transparent"
        border.width: 1
        
        Behavior on color { ColorAnimation { duration: SWMMotion.durationFast } }
    }
    
    SWMIcon {
        anchors.centerIn: parent
        source: root.iconSource
        size: 18
        color: ThemeEngine.textPrimary
    }
    
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
    }
}
