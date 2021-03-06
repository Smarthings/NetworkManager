import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import "../"
import "../dialogs"
import "../components"

ScrollablePage {
    id: root
    property string name
    property string _title: qsTr("Configurações de WiFi")
    property string _icon: "\uE1BA"

    Component.onCompleted: {
        object.structHeader.push({"title": _title, "icon": _icon});
        headerPage.changePage();
    }

    Item {
        width: parent.width
        height: root.height

        Rectangle {
            width: parent.width
            height: root.height
            color: object.background

            ColumnLayout {
                width: object.width
                height: parent.height
                anchors.centerIn: parent

                Item {
                    width: parent.width
                    height: 30

                    Item {
                        anchors.centerIn: parent

                        BusyIndicator {
                            width: 30
                            height: 30
                            visible: wireless.search
                        }
                    }
                }

                Rectangle {
                    width: parent.width
                    Layout.fillHeight: true
                    Layout.topMargin: 10
                    color: "transparent"

                    ListView {
                        width: parent.width
                        height: parent.height
                        clip: true

                        model: wireless.listWifi
                        delegate: ItemDelegate {
                            width: parent.width
                            height: 50
                            highlighted: (modelData.connect)? true : false

                            Column {
                                anchors.fill: parent
                                anchors.margins: 5

                                RowLayout {
                                    width: parent.width
                                    height: 22

                                    Text {
                                        text: modelData.ESSID
                                        color: Material.foreground
                                        font.pixelSize: 18
                                        Layout.fillWidth: true
                                    }
                                    Text {
                                        text: (modelData.Encryption === "on")? "\uE1E1" : "\uE1BA"
                                        color: Material.foreground
                                        font.family: material_icon.name
                                        font.pixelSize: 18
                                    }
                                }
                                RowLayout {
                                    width: parent.width
                                    height: 20

                                    Text {
                                        text: qsTr("Canal: %1").arg(modelData.Channel)
                                        color: Material.foreground
                                        font.pixelSize: 11
                                    }
                                    Text {
                                        text: qsTr("Qualidade: %1%").arg((((modelData.Quality).split("/")[0] / (modelData.Quality).split("/")[1]) * 100).toFixed(0))
                                        color: Material.foreground
                                        font.pixelSize: 10
                                        anchors.right: parent.right
                                    }
                                }
                            }

                            Rectangle {
                                width: parent.width
                                height: 1
                                color: object.line
                                anchors.bottom: parent.bottom
                            }

                            onClicked: {
                                dialogConnect.dataWifi = wireless.listWifi[index];
                                dialogConnect.open();
                            }

                            onPressAndHold: {
                                if (modelData.ESSID === wireless.wifi_connected || modelData.saved) {
                                    dialogDisconnect.name = modelData.ESSID;
                                    dialogDisconnect.open();
                                }
                            }
                        }
                    }
                }
            }
        }
        DialogConnect {
            id: dialogConnect
        }
    }
}
