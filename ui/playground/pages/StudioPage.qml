import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import foundation
import theme
import components

RowLayout {
    id: root
    
    spacing: SWMSpacing.space24
    
    BaseCard {
        title: "Layers & Tools"
        showSettings: false
        Layout.preferredWidth: 260
        Layout.fillHeight: true
        
        ColumnLayout {
            anchors.fill: parent
            spacing: SWMSpacing.space16
            
            ColumnLayout {
                Layout.fillWidth: true
                spacing: SWMSpacing.space8
                
                Repeater {
                    model: ListModel {
                        ListElement { label: "Main Camera Source"; active: true }
                        ListElement { label: "Lower Third Graphics"; active: true }
                        ListElement { label: "Scoreboard Overlay"; active: false }
                        ListElement { label: "Sponsor Crawl Ticker"; active: true }
                        ListElement { label: "Watermark Logo"; active: true }
                    }
                    
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 48
                        radius: SWMRadius.radiusLg
                        color: model.active ? ThemeEngine.primaryLight : ThemeEngine.divider
                        
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: SWMSpacing.space12
                            
                            SWMIcon {
                                source: "file:///" + bootstrap.appDir + "/../resources/icons/eye.svg"
                                size: 16
                                color: model.active ? ThemeEngine.primary : ThemeEngine.textSecondary
                            }
                            
                            Text {
                                text: model.label
                                font.family: SWMTypography.family
                                font.pixelSize: SWMTypography.caption
                                font.weight: SWMTypography.weightMedium
                                color: model.active ? ThemeEngine.primary : ThemeEngine.textSecondary
                                Layout.fillWidth: true
                            }
                            
                            ToggleButton {
                                checked: model.active
                                activeColor: ThemeEngine.primary
                            }
                        }
                    }
                }
            }
            
            Item { Layout.fillHeight: true }
        }
    }
    
    WorkspaceCanvas {
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
