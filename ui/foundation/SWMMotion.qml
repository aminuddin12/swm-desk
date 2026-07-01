pragma Singleton
import QtQuick

QtObject {
    // Duration Tokens
    readonly property int durationFast: 150
    readonly property int durationNormal: 220
    readonly property int durationSlow: 280
    
    // Easing Curves
    readonly property int easingStandard: Easing.OutCubic
    readonly property int easingEntrance: Easing.OutQuint
    readonly property int easingExit: Easing.InCubic
}
