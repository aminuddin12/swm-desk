import QtQuick
import QtQuick.Layouts
import foundation
import theme
import components

Item {
    id: root
    
    property bool isActive: false
    property string iconName: "home"
    property string text: "Item"
    
    signal clicked()
    
    implicitWidth: 80
    implicitHeight: 72
    
    Rectangle {
        anchors.fill: parent
        anchors.margins: SWMSpacing.space4
        radius: SWMRadius.radiusLg
        color: {
            if (mouseArea.pressed) return ThemeEngine.divider
            if (mouseArea.containsMouse) return Qt.rgba(ThemeEngine.divider.r, ThemeEngine.divider.g, ThemeEngine.divider.b, 0.5)
            return "transparent"
        }
        
        Behavior on color { ColorAnimation { duration: SWMMotion.durationFast } }
        
        ColumnLayout {
            anchors.centerIn: parent
            spacing: SWMSpacing.space4
            
            Rectangle {
                width: 40
                height: 40
                radius: SWMRadius.radiusFull
                color: root.isActive ? ThemeEngine.textPrimary : "transparent"
                Layout.alignment: Qt.AlignHCenter
                
                SWMIcon {
                    anchors.centerIn: parent
                    source: "file:///" + bootstrap.appDir + "/../resources/icons/" + root.iconName + ".svg"
                    size: 20
                    color: root.isActive ? ThemeEngine.background : ThemeEngine.textPrimary
                }
                
                Behavior on color { ColorAnimation { duration: SWMMotion.durationFast } }
            }
            
            Text {
                text: root.text
                font.family: SWMTypography.family
                font.pixelSize: SWMTypography.caption
                font.weight: root.isActive ? SWMTypography.weightSemiBold : SWMTypography.weightMedium
                color: root.isActive ? ThemeEngine.textPrimary : ThemeEngine.textSecondary
                Layout.alignment: Qt.AlignHCenter
            }
        }
        
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: root.clicked()
        }
    }
}
