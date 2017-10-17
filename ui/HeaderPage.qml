import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import "./pages"
import "./dialogs"

Rectangle {
    width: parent.width
    height: 60
    color: object.background

    RowLayout {
        anchors.fill: parent
        spacing: 5
        anchors.leftMargin: 5

        ToolButton {
            id: buttonBack
            visible: homePage.stackview.depth > 1
            text: "\uE314"
            font.family: material_icon.name
            font.pixelSize: 28
            Material.foreground: Material.accent

            onClicked: {
                homePage.stackview.pop();
                object.structHeader.pop();
                changePage();
            }
        }

        Label {
            id: iconHeader
            width: 30
            font.family: material_icon.name
            font.pixelSize: 28
            color: Material.accent
        }

        Label {
            id: titleHeader
            Layout.fillWidth: true
            font.pixelSize: 20
            color: Material.accent
        }

        ToolButton {
            id: buttonStyle
            text: "\uE243"
            font.family: material_icon.name
            Material.foreground: Material.accent

            onClicked: {
                dialogTheme.dialog.open()
            }
        }
    }

    Rectangle {
        width: parent.width
        height: 1
        color: object.line
        anchors.bottom: parent.bottom
    }

    function changePage()
    {
        var it = object.structHeader.length -1
        titleHeader.text = object.structHeader[it].title;
        iconHeader.text = object.structHeader[it].icon;
    }
}
