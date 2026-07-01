import QtQuick
import foundation
import theme

Item {
    id: root
    
    property bool checked: false
    property color activeColor: ThemeEngine.primary
    
    implicitWidth: 44
    implicitHeight: 24
    
    Rectangle {
        anchors.fill: parent
        radius: SWMRadius.radiusFull
        color: root.checked ? root.activeColor : ThemeEngine.divider
        
        Behavior on color { ColorAnimation { duration: SWMMotion.durationFast } }
        
        Rectangle {
            id: thumb
            x: root.checked ? parent.width - width - 2 : 2
            y: 2
            width: 20
            height: 20
            radius: SWMRadius.radiusFull
            color: SWMColors.white
            
            // Soft shadow
            border.color: "#1A000000"
            border.width: 1
            
            Behavior on x { NumberAnimation { duration: SWMMotion.durationFast; easing.type: SWMMotion.easingStandard } }
        }
    }
    
    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: root.checked = !root.checked
    }
}
