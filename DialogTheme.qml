import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Item {
    property alias dialog: dialog_theme

    Dialog {
        id: dialog_theme
        title: qsTr("Tema")
        modal: true

        x: Math.round((window.width - width) /2)
        width: 300

        contentItem: Rectangle {
            color: "transparent"
            implicitWidth: parent.width
            implicitHeight: 100

            ListView {
                id: listviewTheme
                width: parent.width
                height: 60
                model: ["Light", "Dark"]
                delegate: RadioDelegate {
                    width: parent.width
                    text: modelData
                    font.weight: Font.Light
                    onCheckedChanged: settings.theme = index
                }
            }
        }
    }
}
