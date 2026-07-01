import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import foundation
import theme
import components

Item {
    id: root
    
    Rectangle {
        anchors.fill: parent
        color: ThemeEngine.surface
        radius: SWMRadius.radius2xl
        
        border.color: ThemeEngine.border
        border.width: 1
        
        ColumnLayout {
            anchors.centerIn: parent
            spacing: SWMSpacing.space16
            
            SWMIcon {
                source: "file:///" + bootstrap.appDir + "/../resources/icons/box.svg"
                size: 64
                color: ThemeEngine.primaryLight
                Layout.alignment: Qt.AlignHCenter
            }
            
            Text {
                text: "Live 3D View"
                font.family: SWMTypography.family
                font.pixelSize: SWMTypography.h2
                font.weight: SWMTypography.weightBold
                color: ThemeEngine.primaryLight
                Layout.alignment: Qt.AlignHCenter
            }
        }
    }
}
