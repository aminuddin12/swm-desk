import QtQuick
import QtQuick.Effects
import foundation
import theme

Item {
    id: root
    
    property string source: ""
    property color color: ThemeEngine.textPrimary
    property int size: 24
    
    implicitWidth: size
    implicitHeight: size
    
    Image {
        id: iconImg
        anchors.fill: parent
        source: root.source
        sourceSize: Qt.size(size, size)
        fillMode: Image.PreserveAspectFit
        smooth: true
        visible: false // Hidden because MultiEffect draws the colored version
    }
    
    MultiEffect {
        source: iconImg
        anchors.fill: iconImg
        colorizationColor: root.color
        colorization: 1.0 // Fully replace color
    }
}
