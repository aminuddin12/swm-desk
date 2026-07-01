import QtQuick

ListModel {
    id: camerasModel
    
    ListElement {
        title: "Outdoor Camera 1"
        subtitle: "Outdoor view"
        active: true
    }
    ListElement {
        title: "Workspace Design"
        subtitle: "Indoor view"
        active: true
    }
    ListElement {
        title: "Main Entrance"
        subtitle: "Indoor view"
        active: false
    }
}
