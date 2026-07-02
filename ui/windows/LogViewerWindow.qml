import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import SWM.Logging 1.0

Window {
    id: logViewerWin
    width: 1400
    height: 850
    minimumWidth: 1400
    minimumHeight: 850
    visible: false
    title: "SWM Runtime Log Viewer"
    color: "#090d16"

    onClosing: (close) => {
        close.accepted = false
        visible = false
    }

    LogListModel {
        id: logModel
    }

    RowLayout {
        anchors.fill: parent
        spacing: 1

        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 280
            color: "#0f172a"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 16

                RowLayout {
                    spacing: 8
                    Text {
                        text: "⚡"
                        font.pixelSize: 18
                        color: "#10b981"
                    }
                    Text {
                        text: "SWM Desk Log Viewer"
                        font.pixelSize: 16
                        font.bold: true
                        color: "#ffffff"
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 6
                    Text {
                        text: "Session"
                        color: "#94a3b8"
                        font.pixelSize: 11
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        height: 32
                        color: "#1e293b"
                        radius: 6
                        border.color: "#334155"
                        TextInput {
                            anchors.fill: parent
                            anchors.margins: 8
                            color: "#cbd5e1"
                            text: logModel.rowCount > 0 ? logModel.getRow(0).sessionId : "-"
                            readOnly: true
                            selectByMouse: true
                            verticalAlignment: TextInput.AlignVCenter
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    Text {
                        text: "Statistics"
                        font.bold: true
                        color: "#ffffff"
                        font.pixelSize: 12
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        height: 160
                        color: "#1e293b"
                        radius: 6
                        border.color: "#334155"

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 12
                            spacing: 6

                            RowLayout {
                                Text { text: "Total Logs"; color: "#94a3b8"; font.pixelSize: 11 }
                                Spacer {}
                                Text { text: String(logStats.totalLogs); color: "#ffffff"; font.pixelSize: 11; font.bold: true }
                            }
                            RowLayout {
                                Text { text: "Displayed"; color: "#94a3b8"; font.pixelSize: 11 }
                                Spacer {}
                                Text { text: String(logModel.rowCount); color: "#ffffff"; font.pixelSize: 11; font.bold: true }
                            }
                            RowLayout {
                                Text { text: "Level (Min)"; color: "#94a3b8"; font.pixelSize: 11 }
                                Spacer {}
                                Text { text: logModel.levelFilter; color: "#ffffff"; font.pixelSize: 11; font.bold: true }
                            }
                            RowLayout {
                                Text { text: "Queue Size"; color: "#94a3b8"; font.pixelSize: 11 }
                                Spacer {}
                                Text { text: String(logStats.queueSize); color: "#ffffff"; font.pixelSize: 11 }
                            }
                            RowLayout {
                                Text { text: "Dropped Logs"; color: "#94a3b8"; font.pixelSize: 11 }
                                Spacer {}
                                Text { text: String(logStats.droppedLogs); color: "#ffffff"; font.pixelSize: 11 }
                            }
                            RowLayout {
                                Text { text: "Flush Count"; color: "#94a3b8"; font.pixelSize: 11 }
                                Spacer {}
                                Text { text: String(logStats.flushCount); color: "#ffffff"; font.pixelSize: 11 }
                            }
                            RowLayout {
                                Text { text: "Last Flush"; color: "#94a3b8"; font.pixelSize: 11 }
                                Spacer {}
                                Text { text: logStats.lastFlush; color: "#ffffff"; font.pixelSize: 11 }
                            }
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    Text {
                        text: "Filters"
                        font.bold: true
                        color: "#ffffff"
                        font.pixelSize: 12
                    }

                    RowLayout {
                        spacing: 8
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4
                            Text { text: "Level"; color: "#94a3b8"; font.pixelSize: 10 }
                            ComboBox {
                                Layout.fillWidth: true
                                model: ["All", "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL"]
                                currentIndex: model.indexOf(logModel.levelFilter)
                                onActivated: (index) => { logModel.levelFilter = model[index] }
                            }
                        }
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4
                            Text { text: "Category"; color: "#94a3b8"; font.pixelSize: 10 }
                            ComboBox {
                                Layout.fillWidth: true
                                model: ["All", "Runtime", "OBS", "UI", "Plugin", "Marketplace"]
                                currentIndex: model.indexOf(logModel.categoryFilter)
                                onActivated: (index) => { logModel.categoryFilter = model[index] }
                            }
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 4
                        Text { text: "Search Query"; color: "#94a3b8"; font.pixelSize: 10 }
                        Rectangle {
                            Layout.fillWidth: true
                            height: 32
                            color: "#1e293b"
                            radius: 6
                            border.color: "#334155"
                            TextInput {
                                anchors.fill: parent
                                anchors.margins: 8
                                color: "#cbd5e1"
                                text: logModel.searchQuery
                                onTextEdited: logModel.searchQuery = text
                                verticalAlignment: TextInput.AlignVCenter
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8
                        CheckBox {
                            text: "Case"
                            checked: logModel.caseSensitive
                            onCheckedChanged: logModel.caseSensitive = checked
                        }
                        CheckBox {
                            text: "Regex"
                            checked: logModel.regexEnabled
                            onCheckedChanged: logModel.regexEnabled = checked
                        }
                        CheckBox {
                            text: "Word"
                            checked: logModel.wholeWord
                            onCheckedChanged: logModel.wholeWord = checked
                        }
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Text {
                        text: "Auto Scroll"
                        color: "#94a3b8"
                        font.pixelSize: 12
                    }
                    Spacer {}
                    Switch {
                        checked: logModel.autoScroll
                        onCheckedChanged: logModel.autoScroll = checked
                    }
                }

                Button {
                    Layout.fillWidth: true
                    text: "Clear Filters"
                    onClicked: logModel.clearFilters()
                }

                Spacer {}

                Text {
                    text: "Connected to MemorySink"
                    color: "#64748b"
                    font.pixelSize: 10
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            Rectangle {
                Layout.fillWidth: true
                height: 50
                color: "#0f172a"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 8

                    Button {
                        text: "All (" + logStats.totalLogs + ")"
                        onClicked: logModel.levelFilter = "All"
                    }
                    Button {
                        text: "TRACE (" + logStats.traceCount + ")"
                        onClicked: logModel.levelFilter = "TRACE"
                    }
                    Button {
                        text: "DEBUG (" + logStats.debugCount + ")"
                        onClicked: logModel.levelFilter = "DEBUG"
                    }
                    Button {
                        text: "INFO (" + logStats.infoCount + ")"
                        onClicked: logModel.levelFilter = "INFO"
                    }
                    Button {
                        text: "WARN (" + logStats.warnCount + ")"
                        onClicked: logModel.levelFilter = "WARN"
                    }
                    Button {
                        text: "ERROR (" + logStats.errorCount + ")"
                        onClicked: logModel.levelFilter = "ERROR"
                    }
                    Button {
                        text: "CRITICAL (" + logStats.criticalCount + ")"
                        onClicked: logModel.levelFilter = "CRITICAL"
                    }

                    Spacer {}

                    Button {
                        text: "Export"
                        onClicked: logExport.exportLogs(bootstrap.getAppDir() + "/../logs/exported.log", "text")
                    }
                    Button {
                        text: "Clear"
                        onClicked: {
                            logModel.clearFilters()
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#090d16"

                ListView {
                    id: logListView
                    anchors.fill: parent
                    anchors.margins: 8
                    model: logModel
                    clip: true
                    currentIndex: -1

                    delegate: ItemDelegate {
                        width: logListView.width
                        height: 32

                        background: Rectangle {
                            color: logListView.currentIndex === index ? "#1e293b" : "transparent"
                        }

                        onClicked: {
                            logListView.currentIndex = index
                        }

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 8
                            anchors.rightMargin: 8
                            spacing: 12

                            Text {
                                text: model.time
                                color: "#94a3b8"
                                font.pixelSize: 11
                                Layout.preferredWidth: 60
                            }

                            Rectangle {
                                Layout.preferredWidth: 60
                                height: 18
                                radius: 4
                                color: model.level === "INFO" ? "#064e3b" :
                                       model.level === "DEBUG" ? "#1e3a8a" :
                                       model.level === "WARN" ? "#78350f" :
                                       model.level === "ERROR" ? "#7f1d1d" :
                                       model.level === "CRITICAL" ? "#581c87" : "#334155"

                                Text {
                                    anchors.centerIn: parent
                                    text: model.level
                                    color: "#ffffff"
                                    font.pixelSize: 9
                                    font.bold: true
                                }
                            }

                            Text {
                                text: model.category
                                color: "#38bdf8"
                                font.pixelSize: 11
                                Layout.preferredWidth: 80
                            }

                            Text {
                                text: model.thread
                                color: "#cbd5e1"
                                font.pixelSize: 11
                                Layout.preferredWidth: 120
                            }

                            Text {
                                text: model.message
                                color: "#ffffff"
                                font.pixelSize: 11
                                Layout.fillWidth: true
                                elide: Text.ElideRight
                            }
                        }
                    }

                    onCountChanged: {
                        if (logModel.autoScroll && count > 0) {
                            positionViewAtEnd()
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 200
                color: "#0f172a"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 8

                    RowLayout {
                        spacing: 12
                        Button { text: "Log Detail" }
                        Button { text: "Raw" }
                        Button { text: "JSON" }
                    }

                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true

                        ColumnLayout {
                            width: parent.width
                            spacing: 4

                            RowLayout {
                                Text { text: "Time:"; color: "#94a3b8"; font.pixelSize: 11; Layout.preferredWidth: 80 }
                                Text { text: logListView.currentIndex >= 0 ? logModel.getRow(logListView.currentIndex).time : "-"; color: "#cbd5e1"; font.pixelSize: 11 }
                            }
                            RowLayout {
                                Text { text: "Level:"; color: "#94a3b8"; font.pixelSize: 11; Layout.preferredWidth: 80 }
                                Text { text: logListView.currentIndex >= 0 ? logModel.getRow(logListView.currentIndex).level : "-"; color: "#cbd5e1"; font.pixelSize: 11 }
                            }
                            RowLayout {
                                Text { text: "Category:"; color: "#94a3b8"; font.pixelSize: 11; Layout.preferredWidth: 80 }
                                Text { text: logListView.currentIndex >= 0 ? logModel.getRow(logListView.currentIndex).category : "-"; color: "#cbd5e1"; font.pixelSize: 11 }
                            }
                            RowLayout {
                                Text { text: "Message:"; color: "#94a3b8"; font.pixelSize: 11; Layout.preferredWidth: 80 }
                                Text { text: logListView.currentIndex >= 0 ? logModel.getRow(logListView.currentIndex).message : "-"; color: "#ffffff"; font.pixelSize: 11; font.bold: true }
                            }
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 24
                color: "#1e293b"

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 12
                    anchors.rightMargin: 12
                    Text {
                        text: "Auto Scroll: " + (logModel.autoScroll ? "ON" : "OFF") + " | Showing " + logModel.rowCount + " logs"
                        color: "#94a3b8"
                        font.pixelSize: 10
                    }
                }
            }
        }
    }
}
