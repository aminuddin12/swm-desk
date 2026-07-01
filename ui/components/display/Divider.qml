import QtQuick
import foundation
import theme

Rectangle {
    id: root
    
    property bool vertical: false
    
    implicitWidth: vertical ? 1 : parent.width
    implicitHeight: vertical ? parent.height : 1
    
    color: ThemeEngine.border
}
