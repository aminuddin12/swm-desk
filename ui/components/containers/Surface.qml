import QtQuick
import foundation
import theme

Rectangle {
    id: root
    
    default property alias content: container.data
    
    color: ThemeEngine.background
    
    Item {
        id: container
        anchors.fill: parent
    }
}
