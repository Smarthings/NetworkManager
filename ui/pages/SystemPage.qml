import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import SystemManager 1.0

import "../"
import "../dialogs"
import "../components"

ScrollablePage {
    id: root

    property string _title: qsTr("Informações do sistema")
    property string _icon: "\uE88E"

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
