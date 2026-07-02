import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import foundation
import theme
import components

ScrollView {
    id: root
    clip: true
    
    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AsNeeded
    }
    
    GridLayout {
        width: parent.width - SWMSpacing.space32
        columns: 3
        rowSpacing: SWMSpacing.space24
        columnSpacing: SWMSpacing.space24
        
        Repeater {
            model: ListModel {
                ListElement { title: "Twitch Overlay Pack"; type: "Stream Graphics"; itemsCount: 12 }
                ListElement { title: "Minimal Lower Thirds"; type: "Broadcast Titles"; itemsCount: 6 }
                ListElement { title: "CS2 HUD Integration"; type: "Gaming HUD"; itemsCount: 4 }
                ListElement { title: "Breaking News Ticker"; type: "Overlay Feed"; itemsCount: 2 }
                ListElement { title: "Podcast Overlay Set"; type: "Social Media Pack"; itemsCount: 8 }
                ListElement { title: "Retro Gaming Overlays"; type: "Classic UI Pack"; itemsCount: 15 }
            }
            
            delegate: BaseCard {
                title: model.title
                showSettings: false
                Layout.fillWidth: true
                Layout.preferredHeight: 180
                
                ColumnLayout {
                    anchors.fill: parent
                    spacing: SWMSpacing.space12
                    
                    Text {
                        text: model.type
                        font.family: SWMTypography.family
                        font.pixelSize: SWMTypography.caption
                        color: ThemeEngine.textSecondary
                    }
                    
                    RowLayout {
                        Layout.fillWidth: true
                        
                        Badge {
                            text: model.itemsCount + " Assets"
                            variant: "primary"
                        }
                        
                        Item { Layout.fillWidth: true }
                        
                        PrimaryButton {
                            text: "Launch"
                            primary: true
                            implicitWidth: 90
                            implicitHeight: 32
                        }
                    }
                }
            }
        }
    }
}
