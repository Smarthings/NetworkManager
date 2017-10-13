import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import SystemManager 1.0

ScrollablePage {
    id: root

    Item {
        width: parent.width
        height: root.height

        Rectangle {
            width: parent.width
            height: root.height
            color: object.background

            Column {
                width: object.width
                height: parent.height
                anchors.centerIn: parent

                Item {
                    width: parent.width
                    height: 10
                }

                RowLayout {
                    width: parent.width
                    height: 50

                    Text {
                        text: "\uE333"
                        font.family: material_icon.name
                        font.pixelSize: object.iconTitleSize
                        color: Material.accent
                    }
                    Text {
                        text: qsTr("Informações do sistema")
                        font.pixelSize: object.titleSize
                        Layout.fillWidth: true
                        color: Material.accent
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: object.line
                }

                Item {
                    width: parent.width
                    height: 20
                }

                Item {
                    width: parent.width

                }
            }
        }

        SystemManager {
            id: system
        }
    }
}
