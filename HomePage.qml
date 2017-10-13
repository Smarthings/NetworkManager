import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Page {
    id: root
    property alias stackview: stackview
    property var menu: [
        {"name": "WiFi", "icon": "\uE63E", "page": "WirelessPage", "color": Material.Red},
        {"name": "Rede Cabeada", "icon": "\uE8BE", "page": "WiredPage", "color": Material.Green},
        {"name": "Bluetooth", "icon": "\uE1A7", "page": "BluetoothPage", "color": Material.Blue},
        {"name": "Brilho da tela", "icon": "\uE1AE", "page": "BrightnessPage", "color": Material.Amber},
        {"name": "Sistema", "icon": "\uE333", "page": "SystemPage", "color": Material.Teal},
    ];
    property string pageCurrent

    Item {
        width: parent.width
        height: root.height

        RowLayout {
            width: parent.width
            height: parent.height -20
            spacing: 10
            anchors.top:parent.top
            anchors.topMargin: 10

            Rectangle {
                Layout.minimumWidth: 200
                Layout.fillHeight: true
                color: object.background

                ListView {
                    anchors.fill: parent
                    clip: true
                    model: menu
                    delegate: ItemDelegate {
                        width: parent.width
                        height: 50

                        RowLayout {
                            anchors.fill: parent

                            Rectangle {
                                width: 28
                                height: 28
                                radius: width
                                color: Material.color(modelData.color)

                                anchors.left: parent.left
                                anchors.leftMargin: 4

                                Text {
                                    anchors.fill: parent
                                    text: modelData.icon
                                    font.family: material_icon.name
                                    font.pixelSize: 20
                                    color: "#fff"

                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }

                            Text {
                                Layout.fillWidth: true
                                Layout.leftMargin: 4
                                text: qsTr(modelData.name)
                                color: object.foreground
                                elide: Text.ElideRight
                                font.pixelSize: 16
                            }

                            Text {
                                Layout.maximumWidth: 28
                                Layout.minimumWidth: 28
                                text: "\uE315"
                                font.family: material_icon.name
                                font.pixelSize: 28
                                color: object.foreground
                            }
                        }

                        onClicked: {
                            pageCurrent = modelData.page
                            stackview.push("qrc:/"+modelData.page+".qml");
                        }
                    }
                }
            }

            StackView {
                id: stackview
                Layout.fillWidth: true
                Layout.minimumWidth: 100
                Layout.fillHeight: true

                initialItem: Page {
                    Rectangle {
                        anchors.fill: parent
                        color: object.background

                        ListView {
                            anchors.fill: parent
                            anchors.margins: 10
                            focus: true
                            clip: true

                            model: manager.getInfo
                            delegate: Item {
                                width: parent.width
                                height: columnlayout_root.implicitHeight + 50

                                ColumnLayout {
                                    id: columnlayout_root
                                    anchors.fill: parent
                                    anchors.margins: 10

                                    Rectangle {
                                        width: parent.width
                                        height: 1
                                        color: object.line
                                    }

                                    Label {
                                        text: modelData.name
                                        font.pixelSize: 18
                                        font.bold: true
                                        color: Material.accent
                                    }

                                    RowLayout {
                                        Layout.fillWidth: true

                                        Text {
                                            text: qsTr("Tipo: ")
                                            font.bold: true
                                            color: Material.foreground
                                        }
                                        Text {
                                            text: (modelData.type)? qsTr(modelData.type) : ""
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
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
ScrollablePage {
    id : root

    Item {
        width: parent.width
        height: root.height

        Rectangle {
            id: root_rectangle
            width: (window.width > 900)? 900 : parent.width
            height: root.height
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter

            GridView {
                id: grid_network
                anchors.fill: parent
                anchors.margins: 10

                focus: true
                clip: true

                cellWidth: 290
                cellHeight: 180

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
                                text: (modelData.type)? qsTr(modelData.type) : ""
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
                                stackview.push("qrc:/WirelessPage.qml", {'name': modelData.name});
                            }
                        }
                    }
                }
            }
        }
    }
}
*/
