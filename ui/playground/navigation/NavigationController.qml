import QtQuick
import QtQuick.Controls.Basic
import foundation
import theme

Item {
    id: root
    
    property string activeTab: "dashboard"
    
    StackView {
        id: stack
        anchors.fill: parent
        
        initialItem: Qt.resolvedUrl("../pages/DashboardPage.qml")
        
        pushEnter: Transition {
            ParallelAnimation {
                NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 220; easing.type: Easing.OutCubic }
                NumberAnimation { property: "x"; from: 20; to: 0; duration: 220; easing.type: Easing.OutCubic }
            }
        }
        pushExit: Transition {
            ParallelAnimation {
                NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 220; easing.type: Easing.OutCubic }
                NumberAnimation { property: "x"; from: 0; to: -20; duration: 220; easing.type: Easing.OutCubic }
            }
        }
        
        popEnter: Transition {
            ParallelAnimation {
                NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 220; easing.type: Easing.OutCubic }
                NumberAnimation { property: "x"; from: -20; to: 0; duration: 220; easing.type: Easing.OutCubic }
            }
        }
        popExit: Transition {
            ParallelAnimation {
                NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 220; easing.type: Easing.OutCubic }
                NumberAnimation { property: "x"; from: 0; to: 20; duration: 220; easing.type: Easing.OutCubic }
            }
        }
    }
    
    function navigateTo(pageName) {
        if (root.activeTab === pageName) {
            return;
        }
        root.activeTab = pageName;
        
        var url = "";
        if (pageName === "dashboard") {
            url = Qt.resolvedUrl("../pages/DashboardPage.qml");
        } else if (pageName === "studio") {
            url = Qt.resolvedUrl("../pages/DashboardPage.qml");
        } else if (pageName === "library") {
            url = Qt.resolvedUrl("../pages/DashboardPage.qml");
        } else if (pageName === "store") {
            url = Qt.resolvedUrl("../pages/DashboardPage.qml");
        }
        
        if (url !== "") {
            stack.replace(url);
        }
    }
}
