import QtQuick
import QtQuick.Layouts
import foundation
import theme
import components

RowLayout {
    id: root
    
    property string activeTab: "dashboard"
    signal tabChanged(string tabName)
    
    Layout.fillWidth: true
    Layout.preferredHeight: 80
    
    spacing: SWMSpacing.space24
    
    RowLayout {
        spacing: SWMSpacing.space12
        Layout.alignment: Qt.AlignVCenter
        
        Rectangle {
            width: 40
            height: 40
            radius: SWMRadius.radiusLg
            color: ThemeEngine.primary
            
            SWMIcon {
                anchors.centerIn: parent
                source: "file:///" + bootstrap.appDir + "/../resources/icons/zap.svg"
                size: 24
                color: SWMColors.white
            }
        }
        
        Text {
            text: "SWM Desk"
            font.family: SWMTypography.family
            font.pixelSize: SWMTypography.h2
            font.weight: SWMTypography.weightBold
            color: ThemeEngine.primary
        }
    }
    
    Item { Layout.fillWidth: true }
    
    RowLayout {
        spacing: SWMSpacing.space12
        Layout.alignment: Qt.AlignCenter
        
        Repeater {
            model: ListModel {
                ListElement { name: "dashboard"; label: "Dashboard"; icon: "home" }
                ListElement { name: "studio"; label: "Studio"; icon: "monitor" }
                ListElement { name: "library"; label: "Library"; icon: "box" }
                ListElement { name: "store"; label: "Store"; icon: "shopping-bag" }
            }
            
            delegate: Rectangle {
                id: tabBtn
                width: Math.max(130, tabLayout.implicitWidth + (SWMSpacing.space16 * 2))
                height: 44
                radius: SWMRadius.radiusFull
                color: root.activeTab === model.name ? ThemeEngine.primary : SWMColors.white
                
                border.color: root.activeTab === model.name ? "transparent" : ThemeEngine.border
                border.width: 1
                
                RowLayout {
                    id: tabLayout
                    anchors.centerIn: parent
                    spacing: SWMSpacing.space8
                    
                    SWMIcon {
                        source: "file:///" + bootstrap.appDir + "/../resources/icons/" + model.icon + ".svg"
                        size: 18
                        color: root.activeTab === model.name ? SWMColors.white : ThemeEngine.primary
                    }
                    
                    Text {
                        text: model.label
                        font.family: SWMTypography.family
                        font.pixelSize: SWMTypography.body
                        font.weight: SWMTypography.weightBold
                        color: root.activeTab === model.name ? SWMColors.white : ThemeEngine.primary
                    }
                }
                
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: root.tabChanged(model.name)
                }
            }
        }
    }
    
    Item { Layout.fillWidth: true }
    
    RowLayout {
        spacing: SWMSpacing.space12
        Layout.alignment: Qt.AlignVCenter
        
        Rectangle {
            id: accountBtn
            width: accountLayout.implicitWidth + (SWMSpacing.space16 * 2)
            height: 44
            radius: SWMRadius.radiusFull
            color: SWMColors.white
            border.color: ThemeEngine.border
            border.width: 1
            
            RowLayout {
                id: accountLayout
                anchors.centerIn: parent
                spacing: SWMSpacing.space8
                
                SWMIcon {
                    source: "file:///" + bootstrap.appDir + "/../resources/icons/user.svg"
                    size: 18
                    color: ThemeEngine.primary
                }
                
                Text {
                    text: "Account"
                    font.family: SWMTypography.family
                    font.pixelSize: SWMTypography.body
                    font.weight: SWMTypography.weightBold
                    color: ThemeEngine.primary
                }
            }
            
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }
        
        Rectangle {
            width: 44
            height: 44
            radius: SWMRadius.radiusFull
            color: SWMColors.white
            border.color: ThemeEngine.border
            border.width: 1
            
            SWMIcon {
                anchors.centerIn: parent
                source: "file:///" + bootstrap.appDir + "/../resources/icons/settings.svg"
                size: 20
                color: ThemeEngine.primary
            }
            
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }
    }
}
