import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import foundation
import theme
import components

RowLayout {
    id: root
    
    spacing: SWMSpacing.space24
    
    BaseCard {
        title: "Preview"
        showSettings: true
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredWidth: 800
        
        Rectangle {
            anchors.fill: parent
            color: ThemeEngine.isDark ? SWMColors.gray700 : SWMColors.gray100
            radius: SWMRadius.radiusLg
        }
    }
    
    ColumnLayout {
        spacing: SWMSpacing.space24
        Layout.fillHeight: true
        Layout.preferredWidth: 400
        
        BaseCard {
            title: "Running Item"
            showSettings: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 450
            
            Rectangle {
                anchors.fill: parent
                color: ThemeEngine.isDark ? SWMColors.gray700 : SWMColors.gray100
                radius: SWMRadius.radiusLg
            }
        }
        
        BaseCard {
            title: "Service"
            showSettings: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 300
            
            Rectangle {
                anchors.fill: parent
                color: ThemeEngine.surface
                radius: SWMRadius.radiusLg
            }
        }
    }
}
