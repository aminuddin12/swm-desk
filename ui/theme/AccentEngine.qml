pragma Singleton
import QtQuick
import foundation

QtObject {
    id: root
    
    // Accents: "Blue", "Purple", "Orange", "Green", "Red", "Pink", "Teal"
    property string currentAccent: "Purple"
    
    readonly property color primary: {
        switch(currentAccent) {
            case "Blue": return SWMColors.blue500
            case "Red": return SWMColors.red500
            case "Green": return SWMColors.green500
            case "Orange": return SWMColors.yellow500
            case "Purple": return SWMColors.purple500
            default: return SWMColors.purple500
        }
    }
    
    readonly property color primaryLight: {
        switch(currentAccent) {
            case "Blue": return "#e0f2fe" // Light Blue
            case "Red": return "#fee2e2"
            case "Green": return "#d1fae5"
            case "Orange": return "#fef3c7"
            case "Purple": return SWMColors.purple100
            default: return SWMColors.purple100
        }
    }
}
