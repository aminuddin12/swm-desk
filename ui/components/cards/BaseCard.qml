import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import foundation
import theme
import components

Item {
    id: root
    
    property int padding: SWMSpacing.space24
    property bool hoverable: false
    property color backgroundColor: ThemeEngine.surface
    property string title: ""
    property bool showSettings: true
    
    default property alias content: container.data
    
    implicitWidth: mainLayout.implicitWidth + (padding * 2)
    implicitHeight: mainLayout.implicitHeight + (padding * 2)
    
    Rectangle {
        id: bgRect
        anchors.fill: parent
        color: root.backgroundColor
        radius: SWMRadius.radius2xl
        border.color: ThemeEngine.border
        border.width: 1
        
        scale: (root.hoverable && mouseArea.containsMouse) ? 1.01 : 1.0
        
        Behavior on scale {
            NumberAnimation { duration: SWMMotion.durationFast; easing.type: SWMMotion.easingStandard }
        }
    }
    
    MultiEffect {
        source: bgRect
        anchors.fill: bgRect
        shadowEnabled: ThemeEngine.mode === "Light"
        shadowColor: "#0A000000"
        shadowHorizontalOffset: 0
        shadowVerticalOffset: (root.hoverable && mouseArea.containsMouse) ? 16 : 8
        shadowBlur: (root.hoverable && mouseArea.containsMouse) ? 0.8 : 0.4
        
        Behavior on shadowVerticalOffset { NumberAnimation { duration: SWMMotion.durationFast } }
        Behavior on shadowBlur { NumberAnimation { duration: SWMMotion.durationFast } }
    }
    
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: root.hoverable
        cursorShape: root.hoverable ? Qt.PointingHandCursor : Qt.ArrowCursor
        acceptedButtons: Qt.NoButton
    }
    
    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: root.padding
        spacing: SWMSpacing.space16
        
        RowLayout {
            Layout.fillWidth: true
            visible: root.title !== ""
            
            Text {
                text: root.title
                font.family: SWMTypography.family
                font.pixelSize: SWMTypography.h3
                font.weight: SWMTypography.weightBold
                color: ThemeEngine.textPrimary
            }
            
            Item { Layout.fillWidth: true }
            
            RowLayout {
                spacing: SWMSpacing.space12
                visible: root.showSettings
                
                Rectangle {
                    width: 1
                    height: 20
                    color: ThemeEngine.border
                }
                
                SWMIcon {
                    source: "file:///" + bootstrap.appDir + "/../resources/icons/settings.svg"
                    size: 20
                    color: ThemeEngine.primary
                    
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
        }
        
        Item {
            id: container
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
