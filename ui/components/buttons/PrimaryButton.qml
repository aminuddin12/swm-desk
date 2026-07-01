import QtQuick
import QtQuick.Layouts
import foundation
import theme
import components

Item {
    id: root
    
    property string text: "Button"
    property string iconSource: ""
    property bool primary: true // true = primary, false = secondary
    
    implicitWidth: Math.max(120, layout.implicitWidth + (SWMSpacing.space24 * 2))
    implicitHeight: 44
    
    property color bgColor: primary ? ThemeEngine.primary : ThemeEngine.primaryLight
    property color textColor: primary ? SWMColors.white : ThemeEngine.primary
    property color hoverColor: primary ? Qt.lighter(ThemeEngine.primary, 1.1) : Qt.darker(ThemeEngine.primaryLight, 1.05)
    
    Rectangle {
        id: bg
        anchors.fill: parent
        radius: SWMRadius.radiusFull
        color: mouseArea.pressed ? Qt.darker(root.hoverColor, 1.1) : (mouseArea.containsMouse ? root.hoverColor : root.bgColor)
        
        Behavior on color {
            ColorAnimation { duration: SWMMotion.durationFast; easing.type: SWMMotion.easingStandard }
        }
    }
    
    RowLayout {
        id: layout
        anchors.centerIn: parent
        spacing: SWMSpacing.space8
        
        SWMIcon {
            source: root.iconSource
            visible: root.iconSource !== ""
            size: 18
            color: root.textColor
        }
        
        Text {
            text: root.text
            font.family: SWMTypography.family
            font.pixelSize: SWMTypography.body
            font.weight: SWMTypography.weightMedium
            color: root.textColor
        }
    }
    
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
    }
}
