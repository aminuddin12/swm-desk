pragma Singleton
import QtQuick

QtObject {
    // Accessibility parameters
    property real uiScale: 1.0
    property bool reducedMotion: false
    property bool highContrast: false
    
    // Focus ring configuration
    readonly property int focusRingWidth: 2
    readonly property int focusRingOffset: 2
}
