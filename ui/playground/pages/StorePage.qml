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
    
    ColumnLayout {
        width: parent.width - SWMSpacing.space32
        spacing: SWMSpacing.space32
        
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 180
            radius: SWMRadius.radius2xl
            color: ThemeEngine.primary
            
            gradient: Gradient {
                GradientStop { position: 0.0; color: ThemeEngine.primary }
                GradientStop { position: 1.0; color: Qt.lighter(ThemeEngine.primary, 1.2) }
            }
            
            RowLayout {
                anchors.fill: parent
                anchors.margins: SWMSpacing.space32
                spacing: SWMSpacing.space24
                
                ColumnLayout {
                    spacing: SWMSpacing.space8
                    Layout.fillWidth: true
                    
                    Text {
                        text: "Premium Broadcast Bundle"
                        font.family: SWMTypography.family
                        font.pixelSize: SWMTypography.h2
                        font.weight: SWMTypography.weightBold
                        color: SWMColors.white
                    }
                    
                    Text {
                        text: "Get access to over 50+ animated overlay templates, lower-thirds, and widgets."
                        font.family: SWMTypography.family
                        font.pixelSize: SWMTypography.body
                        color: Qt.rgba(255, 255, 255, 0.8)
                    }
                }
                
                PrimaryButton {
                    text: "Claim 50% Off"
                    primary: false
                    bgColor: SWMColors.white
                    textColor: ThemeEngine.primary
                    implicitWidth: 150
                    implicitHeight: 44
                }
            }
        }
        
        RowLayout {
            Layout.fillWidth: true
            spacing: SWMSpacing.space16
            
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 44
                radius: SWMRadius.radiusFull
                color: ThemeEngine.surface
                border.color: ThemeEngine.border
                border.width: 1
                
                RowLayout {
                    anchors.fill: parent
                    anchors.margins: SWMSpacing.space12
                    
                    SWMIcon {
                        source: "file:///" + bootstrap.appDir + "/../resources/icons/search.svg"
                        size: 16
                        color: ThemeEngine.textSecondary
                    }
                    
                    TextInput {
                        id: searchInput
                        font.family: SWMTypography.family
                        font.pixelSize: SWMTypography.body
                        color: ThemeEngine.textPrimary
                        Layout.fillWidth: true
                    }
                }
            }
            
            RowLayout {
                spacing: SWMSpacing.space8
                
                Repeater {
                    model: ListModel {
                        ListElement { label: "All"; active: true }
                        ListElement { label: "Lower Thirds"; active: false }
                        ListElement { label: "Widgets"; active: false }
                        ListElement { label: "Gaming HUDs"; active: false }
                    }
                    
                    delegate: Rectangle {
                        width: filterLayout.implicitWidth + (SWMSpacing.space16 * 2)
                        height: 44
                        radius: SWMRadius.radiusFull
                        color: model.active ? ThemeEngine.primaryLight : ThemeEngine.surface
                        border.color: model.active ? "transparent" : ThemeEngine.border
                        border.width: 1
                        
                        RowLayout {
                            id: filterLayout
                            anchors.centerIn: parent
                            
                            Text {
                                text: model.label
                                font.family: SWMTypography.family
                                font.pixelSize: SWMTypography.caption
                                font.weight: SWMTypography.weightBold
                                color: model.active ? ThemeEngine.primary : ThemeEngine.textSecondary
                            }
                        }
                        
                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                }
            }
        }
        
        GridLayout {
            Layout.fillWidth: true
            columns: 3
            rowSpacing: SWMSpacing.space24
            columnSpacing: SWMSpacing.space24
            
            Repeater {
                model: ListModel {
                    ListElement { title: "Minimalist News Pack"; price: "$19"; rating: "4.9" }
                    ListElement { title: "Valorant Stream Widget"; price: "$29"; rating: "4.8" }
                    ListElement { title: "Neon Cyberpunk HUD"; price: "$15"; rating: "4.7" }
                    ListElement { title: "Election Results Ticker"; price: "$49"; rating: "5.0" }
                    ListElement { title: "Soccer Scoreboard V2"; price: "$35"; rating: "4.9" }
                    ListElement { title: "Podcast Lower-Thirds Pack"; price: "$12"; rating: "4.6" }
                }
                
                delegate: BaseCard {
                    title: model.title
                    showSettings: false
                    Layout.fillWidth: true
                    Layout.preferredHeight: 200
                    
                    ColumnLayout {
                        anchors.fill: parent
                        spacing: SWMSpacing.space16
                        
                        RowLayout {
                            Layout.fillWidth: true
                            
                            Text {
                                text: "Rating: ★ " + model.rating
                                font.family: SWMTypography.family
                                font.pixelSize: SWMTypography.caption
                                color: ThemeEngine.warning
                            }
                        }
                        
                        RowLayout {
                            Layout.fillWidth: true
                            
                            Text {
                                text: model.price
                                font.family: SWMTypography.family
                                font.pixelSize: SWMTypography.h3
                                font.weight: SWMTypography.weightBold
                                color: ThemeEngine.textPrimary
                            }
                            
                            Item { Layout.fillWidth: true }
                            
                            PrimaryButton {
                                text: "Purchase"
                                primary: true
                                implicitWidth: 100
                                implicitHeight: 36
                            }
                        }
                    }
                }
            }
        }
    }
}
