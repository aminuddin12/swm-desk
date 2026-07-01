import QtQuick
import QtQuick.Layouts
import foundation
import theme
import components

RowLayout {
    id: root
    
    property string title: "Dashboard"
    
    Layout.fillWidth: true
    Layout.preferredHeight: 64
    
    spacing: SWMSpacing.space16
    
    Text {
        text: root.title
        font.family: SWMTypography.family
        font.pixelSize: SWMTypography.h1
        font.weight: SWMTypography.weightBold
        color: ThemeEngine.textPrimary
        Layout.alignment: Qt.AlignVCenter
    }
    
    Item { Layout.fillWidth: true } // Flexible spacer
    
    // Actions
    IconButton {
        iconSource: "file:///" + bootstrap.appDir + "/../resources/icons/" + (ThemeEngine.mode === "Light" ? "moon" : "sun") + ".svg"
        ghost: true
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: ThemeEngine.mode = ThemeEngine.mode === "Light" ? "Dark" : "Light"
        }
    }
    
    IconButton {
        iconSource: "file:///" + bootstrap.appDir + "/../resources/icons/bell.svg"
        ghost: true
    }
    
    PrimaryButton {
        text: "Add Device"
        iconSource: "file:///" + bootstrap.appDir + "/../resources/icons/plus.svg"
        primary: true
        Layout.leftMargin: SWMSpacing.space8
        Layout.rightMargin: SWMSpacing.space8
    }
    
    Rectangle {
        width: 40
        height: 40
        radius: SWMRadius.radiusFull
        color: ThemeEngine.divider
        Layout.alignment: Qt.AlignVCenter
        
        Text {
            anchors.centerIn: parent
            text: "A"
            font.family: SWMTypography.family
            font.pixelSize: SWMTypography.body
            font.weight: SWMTypography.weightBold
            color: ThemeEngine.textPrimary
        }
    }
}
