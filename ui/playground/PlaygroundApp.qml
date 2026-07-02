import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import foundation
import theme
import components
import "navigation" as Nav

ApplicationWindow {
    id: window
    width: 1400
    height: 900
    visible: true
    title: "Dashboard | SWM Desk"
    
    color: ThemeEngine.background
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: SWMSpacing.space32
        spacing: SWMSpacing.space24
        
        TopBar {
            id: topBar
            activeTab: navController.activeTab
            onTabChanged: (tabName) => {
                navController.navigateTo(tabName)
            }
        }
        
        Text {
            text: navController.activeTab.charAt(0).toUpperCase() + navController.activeTab.slice(1)
            font.family: SWMTypography.family
            font.pixelSize: SWMTypography.h1
            font.weight: SWMTypography.weightBold
            color: ThemeEngine.textPrimary
            Layout.fillWidth: true
        }
        
        Nav.NavigationController {
            id: navController
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
