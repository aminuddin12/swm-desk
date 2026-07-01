import QtQuick
import QtQuick.Layouts
import foundation
import theme
import components

Rectangle {
    id: root
    
    implicitWidth: 100
    color: "transparent"
    
    signal navigate(string page)
    property string activePage: "dashboard"
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: SWMSpacing.space16
        spacing: SWMSpacing.space16
        
        // Brand Logo
        Rectangle {
            width: 48
            height: 48
            radius: SWMRadius.radiusFull
            color: ThemeEngine.primaryLight
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: SWMSpacing.space8
            Layout.bottomMargin: SWMSpacing.space24
            
            Text {
                anchors.centerIn: parent
                text: "i"
                font.family: SWMTypography.family
                font.pixelSize: 24
                font.weight: SWMTypography.weightBold
                font.italic: true
                color: ThemeEngine.primary
            }
        }
        
        // Nav Items
        ColumnLayout {
            spacing: SWMSpacing.space8
            Layout.alignment: Qt.AlignHCenter
            
            SidebarItem {
                iconName: "home"
                text: "Home"
                isActive: root.activePage === "dashboard"
                onClicked: root.navigate("dashboard")
            }
            
            SidebarItem {
                iconName: "eye"
                text: "Live View"
                isActive: root.activePage === "live"
                onClicked: root.navigate("live")
            }
            
            SidebarItem {
                iconName: "layout-dashboard"
                text: "Devices"
                isActive: root.activePage === "devices"
                onClicked: root.navigate("devices")
            }
            
            SidebarItem {
                iconName: "box"
                text: "Assets"
                isActive: root.activePage === "assets"
                onClicked: root.navigate("assets")
            }
        }
        
        Item { Layout.fillHeight: true }
        
        // Bottom settings
        SidebarItem {
            iconName: "settings"
            text: "Settings"
            isActive: root.activePage === "settings"
            onClicked: root.navigate("settings")
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
