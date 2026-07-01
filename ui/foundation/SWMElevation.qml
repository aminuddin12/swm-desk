pragma Singleton
import QtQuick

QtObject {
    // Define properties for depth, shadows, and z-indexes
    readonly property int level0: 0
    readonly property int level1: 1
    readonly property int level2: 2
    readonly property int level3: 3
    readonly property int level4: 4
    readonly property int level5: 5
    
    // Abstract Z-Index boundaries
    readonly property int zIndexBase: 0
    readonly property int zIndexOverlay: 100
    readonly property int zIndexDialog: 200
    readonly property int zIndexToast: 300
    readonly property int zIndexTooltip: 400
}
