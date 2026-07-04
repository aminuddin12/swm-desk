import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import SWM.Graphics 1.0

Window {
    id: graphicsPreviewWin
    width: 1400
    height: 850
    minimumWidth: 1400
    minimumHeight: 850
    visible: false
    title: "SWM Graphics Preview"
    color: "#090d16"

    onClosing: (close) => {
        close.accepted = false
        visible = false
    }

    RowLayout {
        anchors.fill: parent
        spacing: 1

        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 320
            color: "#0f172a"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 16

                Text {
                    text: "SWM Graphics Preview"
                    color: "#f8fafc"
                    font.pixelSize: 20
                    font.weight: Font.Bold
                    Layout.fillWidth: true
                }

                Rectangle {
                    Layout.fillWidth: true
                    height: 1
                    color: "#1e293b"
                }

                GridLayout {
                    columns: 2
                    rowSpacing: 12
                    columnSpacing: 16
                    Layout.fillWidth: true

                    Text { text: "Backend"; color: "#94a3b8"; font.pixelSize: 13 }
                    Text { text: graphicsStats ? graphicsStats.backendName : "-"; color: "#f8fafc"; font.pixelSize: 13; font.weight: Font.Medium; Layout.fillWidth: true; elide: Text.ElideRight }

                    Text { text: "Engine"; color: "#94a3b8"; font.pixelSize: 13 }
                    Text { text: graphicsStats ? graphicsStats.engineVersion : "-"; color: "#f8fafc"; font.pixelSize: 13; font.weight: Font.Medium; Layout.fillWidth: true; elide: Text.ElideRight }

                    Text { text: "Resolution"; color: "#94a3b8"; font.pixelSize: 13 }
                    Text { text: graphicsStats ? (graphicsStats.resolutionWidth + "x" + graphicsStats.resolutionHeight) : "-"; color: "#f8fafc"; font.pixelSize: 13; font.weight: Font.Medium; Layout.fillWidth: true; elide: Text.ElideRight }

                    Text { text: "FPS Target"; color: "#94a3b8"; font.pixelSize: 13 }
                    Text { text: "30"; color: "#f8fafc"; font.pixelSize: 13; font.weight: Font.Medium; Layout.fillWidth: true; elide: Text.ElideRight }

                    Text { text: "Frame Count"; color: "#94a3b8"; font.pixelSize: 13 }
                    Text { text: graphicsStats ? graphicsStats.frameCount : "0"; color: "#f8fafc"; font.pixelSize: 13; font.weight: Font.Medium; Layout.fillWidth: true; elide: Text.ElideRight }

                    Text { text: "Render Time"; color: "#94a3b8"; font.pixelSize: 13 }
                    Text { text: graphicsStats ? (graphicsStats.lastRenderDurationMs.toFixed(3) + " ms") : "0 ms"; color: "#f8fafc"; font.pixelSize: 13; font.weight: Font.Medium; Layout.fillWidth: true; elide: Text.ElideRight }

                    Text { text: "Avg Render"; color: "#94a3b8"; font.pixelSize: 13 }
                    Text { text: graphicsStats ? (graphicsStats.averageRenderDurationMs.toFixed(3) + " ms") : "0 ms"; color: "#f8fafc"; font.pixelSize: 13; font.weight: Font.Medium; Layout.fillWidth: true; elide: Text.ElideRight }
                }

                Item { Layout.fillHeight: true }

                ColumnLayout {
                    spacing: 8
                    Layout.fillWidth: true

                    Button {
                        Layout.fillWidth: true
                        height: 40
                        text: "Render Once"
                        font.pixelSize: 14
                        font.weight: Font.Medium
                        
                        background: Rectangle {
                            color: parent.pressed ? "#1d4ed8" : parent.hovered ? "#2563eb" : "#3b82f6"
                            radius: 6
                        }
                        
                        contentItem: Text {
                            text: parent.text
                            color: "#ffffff"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font: parent.font
                        }
                        
                        onClicked: {
                            previewItem.renderOnce();
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8
                        
                        Button {
                            Layout.fillWidth: true
                            height: 40
                            text: "Start Render"
                            font.pixelSize: 14
                            font.weight: Font.Medium
                            
                            background: Rectangle {
                                color: parent.pressed ? "#047857" : parent.hovered ? "#059669" : "#10b981"
                                radius: 6
                            }
                            
                            contentItem: Text {
                                text: parent.text
                                color: "#ffffff"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font: parent.font
                            }
                            
                            onClicked: {
                                previewItem.startRender();
                            }
                        }

                        Button {
                            Layout.fillWidth: true
                            height: 40
                            text: "Stop"
                            font.pixelSize: 14
                            font.weight: Font.Medium
                            
                            background: Rectangle {
                                color: parent.pressed ? "#be123c" : parent.hovered ? "#e11d48" : "#f43f5e"
                                radius: 6
                            }
                            
                            contentItem: Text {
                                text: parent.text
                                color: "#ffffff"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font: parent.font
                            }
                            
                            onClicked: {
                                previewItem.stopRender();
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#020617"
            
            GraphicsPreviewItem {
                id: previewItem
                anchors.centerIn: parent
                // Scale to fit while maintaining aspect ratio
                width: Math.min(parent.width - 40, (parent.height - 40) * (1920/1080))
                height: width * (1080/1920)
                
                Component.onCompleted: {
                    if (graphicsRuntime) {
                        setRuntime(graphicsRuntime);
                        setSessionId(graphicsRuntime.defaultPreviewSessionId);
                    }
                }
            }
            
            // Checkerboard background for transparency
            Rectangle {
                anchors.fill: previewItem
                z: -1
                color: "#1e293b"
                
                Canvas {
                    anchors.fill: parent
                    onPaint: {
                        var ctx = getContext("2d");
                        var squareSize = 20;
                        for (var i = 0; i < width; i += squareSize) {
                            for (var j = 0; j < height; j += squareSize) {
                                ctx.fillStyle = (i / squareSize % 2 === j / squareSize % 2) ? "#334155" : "#1e293b";
                                ctx.fillRect(i, j, squareSize, squareSize);
                            }
                        }
                    }
                }
            }
        }
    }
}
