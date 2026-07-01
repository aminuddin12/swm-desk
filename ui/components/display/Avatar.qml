import QtQuick
import foundation
import theme

Rectangle {
    id: root
    
    property string source: ""
    property string initials: "A"
    
    implicitWidth: 40
    implicitHeight: 40
    
    radius: SWMRadius.radiusFull
    color: ThemeEngine.primaryLight
    
    border.color: ThemeEngine.border
    border.width: 1
    
    Text {
        anchors.centerIn: parent
        text: root.initials
        font.family: SWMTypography.family
        font.pixelSize: 16
        font.weight: SWMTypography.weightBold
        color: ThemeEngine.primary
    }
}
