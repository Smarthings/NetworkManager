import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Dialog {
    id: dialog_connect

    property var dataWifi: []
    property bool visiblePass: false

    title: qsTr("Conectar a uma rede WIFI")
    modal: true

    x: Math.round((window.width - width) /2)
    width: 350

    standardButtons: Dialog.Cancel | Dialog.Save
    contentItem: Item {
        width: parent.width
        height: parent.height

        ColumnLayout {
            anchors.fill: parent

            Text {
                text: (dataWifi['ESSID'])? dataWifi['ESSID'] : ""
                font.bold: true
                color: Material.foreground
            }

            RowLayout {
                Layout.fillWidth: true

                TextField {
                    id: password
                    Layout.fillWidth: true
                    placeholderText: qsTr("Senha")
                    focus: true
                    echoMode: visiblePass? TextInput.Normal : TextInput.Password
                }

                Button {
                    width: 20
                    text: visiblePass? "\uE8F5" : "\uE8F4"
                    font.family: material_icon.name
                    flat: true

                    onClicked: visiblePass = !visiblePass
                }
            }
        }
    }

    onAccepted: {
        dataWifi['password'] = password.text;
        wireless.setWifi(dataWifi);
        dialogConnect.close();
    }

    onDataWifiChanged: {
        //console.log(JSON.stringify(dataWifi));
    }
}
