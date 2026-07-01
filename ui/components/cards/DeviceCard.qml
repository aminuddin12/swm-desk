import QtQuick
import QtQuick.Layouts
import foundation
import theme
import components

BaseCard {
    id: root
    padding: SWMSpacing.space24
    
    property string title: "Card Title"
    property string subtitle: "Card Subtitle"
    property string actionText: ""
    property bool actionEnabled: false
    
    // Custom container to handle the standard header
    Item {
        anchors.fill: parent
        
        ColumnLayout {
            anchors.fill: parent
            spacing: SWMSpacing.space16
            
            // Header
            RowLayout {
                Layout.fillWidth: true
                
                ColumnLayout {
                    spacing: 4
                    Text {
                        text: root.title
                        font.family: SWMTypography.family
                        font.pixelSize: SWMTypography.h3
                        font.weight: SWMTypography.weightBold
                        color: ThemeEngine.textPrimary
                    }
                    Text {
                        text: root.subtitle
                        font.family: SWMTypography.family
                        font.pixelSize: SWMTypography.caption
                        color: ThemeEngine.textSecondary
                        visible: root.subtitle !== ""
                    }
                }
                
                Item { Layout.fillWidth: true } // Spacer
                
                Text {
                    text: root.actionText
                    font.family: SWMTypography.family
                    font.pixelSize: SWMTypography.caption
                    font.weight: SWMTypography.weightMedium
                    color: ThemeEngine.primary
                    visible: root.actionEnabled
                    
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
            
            // Slot for actual content
            Item {
                id: contentSlot
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
    
    // Override default property to point to the inner content slot
    default property alias content: contentSlot.data
}
