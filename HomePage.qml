import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0

ScrollablePage {
    id : root

    Item {
        width: parent.width
        height: root.height

        Rectangle {
            id: root_rectangle
            width: (window.width > 900)? 900 : parent.width
            height: parent.height
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter

            GridView {
                id: grid_network
                anchors.fill: parent
                anchors.margins: 10

                focus: true
                clip: true

                cellWidth: 290
                cellHeight: 160

                model: manager.getInfo
                delegate: Rectangle {
                    width: grid_network.cellWidth -10
                    height: grid_network.cellHeight -10
                    border.color: object.line
                    radius: 5
                    color: object.background

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 10

                        RowLayout {
                            Layout.fillWidth: true

                            Text {
                                text: qsTr("Interface: ")
                                font.bold: true
                                color: Material.foreground
                            }
                            Text {
                                text: modelData.name
                                Layout.fillWidth: true
                                color: Material.foreground
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true

                            Text {
                                text: qsTr("Tipo: ")
                                font.bold: true
                                color: Material.foreground
                            }
                            Text {
                                text: qsTr(modelData.type)
                                font.capitalization: Font.Capitalize
                                Layout.fillWidth: true
                                color: Material.foreground
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true

                            Text {
                                text: qsTr("Status: ")
                                font.bold: true
                                color: Material.foreground
                            }
                            Text {
                                text: modelData.status? qsTr("Ativa") : qsTr("Inativa")
                                Layout.fillWidth: true
                                color: Material.foreground
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            visible: modelData.ssid? true : false

                            Text {
                                text: qsTr("WiFi: ")
                                font.bold: true
                                color: Material.foreground
                            }
                            Text {
                                text: modelData.ssid? modelData.ssid : ""
                                Layout.fillWidth: true
                                color: Material.foreground
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true

                            Text {
                                text: qsTr("IP: ")
                                font.bold: true
                                color: Material.foreground
                            }
                            Text {
                                text: (modelData.ipaddress)? modelData.ipaddress: ""
                                Layout.fillWidth: true
                                color: Material.foreground
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true

                            Text {
                                text: qsTr("Mascara de rede: ")
                                font.bold: true
                                color: Material.foreground
                            }
                            Text {
                                text: (modelData.netmask)? modelData.netmask : ""
                                Layout.fillWidth: true
                                color: Material.foreground
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true

                            Text {
                                text: qsTr("Broadcast: ")
                                font.bold: true
                                color: Material.foreground
                            }
                            Text {
                                text: (modelData.broadcast)? modelData.broadcast : ""
                                Layout.fillWidth: true
                                color: Material.foreground
                            }
                        }
                    }

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            if (modelData.type === "wired") {

                            }
                            if (modelData.type === "wireless") {
                                wireless.startService(modelData.name);
                                stackview.push("qrc:/WirelessPage.qml", {'name': modelData.name});
                            }
                        }
                    }
                }
            }
        }
    }
}
