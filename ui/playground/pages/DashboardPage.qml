import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import foundation
import theme
import components
import "../models"

Item {
    id: root
    
    CamerasModel { id: camerasModel }
    
    GridLayout {
        anchors.fill: parent
        columns: 3
        columnSpacing: SWMSpacing.space24
        rowSpacing: SWMSpacing.space24
        
        // LEFT PANEL (CCTVs & Door)
        Column {
            Layout.fillHeight: true
            Layout.preferredWidth: 320
            spacing: SWMSpacing.space24
            
            BaseCard {
                width: parent.width
                
                Column {
                    width: parent.width
                    spacing: SWMSpacing.space16
                    
                    Row {
                        width: parent.width
                        Column {
                            SectionTitle { text: "CCTVs" }
                            Text { text: camerasModel.count + " Devices"; font.pixelSize: SWMTypography.caption; color: ThemeEngine.textSecondary }
                        }
                    }
                    
                    Repeater {
                        model: camerasModel
                        delegate: DeviceCard {
                            width: parent.width
                            title: model.title
                            subtitle: model.subtitle
                            
                            Row {
                                anchors.right: parent.right
                                anchors.verticalCenter: parent.verticalCenter
                                ToggleButton { checked: model.active }
                            }
                        }
                    }
                }
            }
        }
        
        // CENTER CANVAS (3D View)
        WorkspaceCanvas {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        
        // RIGHT PANEL
        Column {
            Layout.fillHeight: true
            Layout.preferredWidth: 320
            spacing: SWMSpacing.space24
            
            BaseCard {
                width: parent.width
                Column {
                    width: parent.width
                    spacing: SWMSpacing.space16
                    
                    SectionTitle { text: "Lighting" }
                    
                    Rectangle {
                        width: parent.width
                        height: 120
                        color: ThemeEngine.divider
                        radius: SWMRadius.radiusLg
                        SWMIcon {
                            anchors.centerIn: parent
                            source: "file:///" + bootstrap.appDir + "/../resources/icons/sun.svg"
                            size: 48
                            color: ThemeEngine.warning
                        }
                    }
                }
            }
        }
    }
}
