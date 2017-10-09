import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Dialog {
    id: dialog_connect

    property var dataWifi: []
    property bool visiblePass: false

    title: qsTr("Conectar à rede WIFI")
    modal: true

    x: Math.round((window.width - width) /2)
    width: 350

    //standardButtons: Dialog.Cancel | Dialog.Save
    contentItem: Item {
        width: parent.width
        height: parent.height

        ColumnLayout {
            anchors.fill: parent

            Text {
                text: (dataWifi['ESSID'])? dataWifi['ESSID'] : ""
                font.pixelSize: 16
                font.bold: true
                color: Material.foreground
            }

            RowLayout {
                Layout.fillWidth: true
                enabled: !dataWifi['saved']
                visible: !dataWifi['saved']

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

    footer: ColumnLayout {
        id: footer_column
        width: parent.width

        Button {
            Layout.fillWidth: true
            height: 50
            text: qsTr("Conectar");
            Material.background: Material.Green

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            onClicked: {
                if (dataWifi['saved']) {
                    console.log("Connect: ", dataWifi['id']);
                } else {
                    dataWifi['password'] = password.text;
                    wireless.setWifi(dataWifi);
                }
                dialogConnect.close();
            }
        }

        Button {
            enabled: wireless.wifi_connected === dataWifi['ESSID']
            visible: wireless.wifi_connected === dataWifi['ESSID']

            Layout.fillWidth: true
            height: 50
            text: qsTr("Desconectar");
            Material.background: Material.accent

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
        }

        Button {
            enabled: !dataWifi['saved']? false : true
            visible: !dataWifi['saved']? false : true

            Layout.fillWidth: true
            height: 50
            text: qsTr("Esquecer esta rede");
            Material.background: Material.Red

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
        }
    }

    onDataWifiChanged: {
        //console.log(JSON.stringify(dataWifi));
    }
}