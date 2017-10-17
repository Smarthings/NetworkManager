import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import "../"
import "../dialogs"
import "../components"

ScrollablePage {
    id: root

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

                Header {
                    width: parent.width

                    _title: qsTr("Rede Cabeada")
                    _icon: "\uE8BE"
                    _font: material_icon.name
                }

                Item {
                    width: parent.width
                    height: 20
                }

                Item {
                    width: parent.width
                    Layout.fillHeight: true
                }
            }
        }
    }
}
