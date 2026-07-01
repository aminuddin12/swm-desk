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
    title: "SWM Desk - Premium Playground"
    
    color: ThemeEngine.background
    
    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        // SIDEBAR
        Sidebar {
            Layout.fillHeight: true
            onNavigate: (page) => {
                navController.navigateTo(page)
            }
        }
        
        // MAIN WORKSPACE
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: SWMSpacing.space24
            Layout.rightMargin: SWMSpacing.space32
            
            // TOP BAR
            TopBar {
                title: "Live 3D OfficeSpace View"
                Layout.topMargin: SWMSpacing.space32
            }
            
            // NAVIGATION AREA
            Nav.NavigationController {
                id: navController
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.bottomMargin: SWMSpacing.space32
            }
        }
    }
}
