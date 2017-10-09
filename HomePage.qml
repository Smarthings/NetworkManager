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
            width: (window.width > 400)? 400 : parent.width
            height: parent.height
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter


        }
    }
}
