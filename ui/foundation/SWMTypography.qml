pragma Singleton
import QtQuick

QtObject {
    id: root
    
    property FontLoader interFont: FontLoader {
        source: Qt.resolvedUrl("../../resources/fonts/Inter-VariableFont.ttf")
    }
    
    readonly property string family: interFont.status === FontLoader.Ready ? interFont.name : "SF Pro"
    
    // Base Sizes
    readonly property int h1: 32
    readonly property int h2: 24
    readonly property int h3: 20
    readonly property int h4: 18
    readonly property int bodyLarge: 16
    readonly property int body: 14
    readonly property int caption: 12
    readonly property int micro: 10
    
    // Weights
    readonly property int weightRegular: Font.Normal
    readonly property int weightMedium: Font.Medium
    readonly property int weightSemiBold: Font.DemiBold
    readonly property int weightBold: Font.Bold
}
