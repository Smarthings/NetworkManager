import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0

ScrollablePage {
    id: homePage

    Item {
        width: parent.width
        height: homePage.height

        Rectangle {
            width: (window.width > 400)? 400 : parent.width
            height: parent.height
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter

            ColumnLayout {
                anchors.fill: parent
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10

                Item {
                    width: parent.width
                    height: 20
                }

                RowLayout {
                    width: parent.width
                    height: 50

                    Text {
                        text: "\uE1BA"
                        font.family: material_icon.name
                        font.pixelSize: 50
                        color: Material.accent
                    }

                    Text {
                        text: qsTr("Conecte-se a uma rede WIFI")
                        font.pixelSize: 20
                        Layout.fillWidth: true
                        color: Material.accent
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: "#ddd"
                }

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
                    color: "transparent"

                    ListView {
                        width: parent.width
                        height: parent.height
                        clip: true

                        model: wireless.listWifi
                        delegate: ItemDelegate {
                            width: parent.width
                            height: 50

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
                                color: "#ddd"
                                anchors.bottom: parent.bottom
                            }
                        }
                    }
                }
            }
        }
    }
}