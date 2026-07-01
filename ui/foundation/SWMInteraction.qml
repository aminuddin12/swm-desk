pragma Singleton
import QtQuick

QtObject {
    // Minimum touch/click target size per modern standards
    readonly property int minHitboxSize: 44
    
    // Press thresholds
    readonly property int longPressDuration: 500
}
