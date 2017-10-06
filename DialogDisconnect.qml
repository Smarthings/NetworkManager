import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Dialog {
    id: dialog_disconnect

    property string name

    title: name;
    modal: true

    x: Math.round((window.width - width) /2)
    width: 300
    height: implicitHeight

    contentItem: Page {
        id: contentPage
        width: parent.width

        Column {
            anchors.fill: parent
            spacing: 20

            Button {
                width: parent.width
                height: 50
                text: qsTr("Desconectar");

                Material.background: Material.accent
            }

            Button {
                width: parent.width
                height: 50
                text: qsTr("Esquecer esta rede");

                Material.background: Material.Red
            }
        }
    }
}
