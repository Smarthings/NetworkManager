import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Dialog {
    id: dialog_connect

    property var dataWifi: []
    property bool visiblePass: false

    title: (dataWifi['ESSID'])? dataWifi['ESSID'] : ""
    modal: true

    x: Math.round((width - (window.width - root.width)) /4)
    width: 350

    contentItem: Item {
        width: parent.width
        height: parent.height

        ColumnLayout {
            anchors.fill: parent

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
            enabled: wireless.wifi_connected !== dataWifi['ESSID']
            visible: wireless.wifi_connected !== dataWifi['ESSID']

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
                    wireless.connectWifi(dataWifi['ESSID'], dataWifi['saved']);
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
            Material.background: Material.BlueGrey

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            onClicked: {
                wireless.disconnectWifi();
                dialogConnect.close();
            }
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

            onClicked: {
                wireless.forgetNetwork(dataWifi);
                wireless.disconnectWifi();
                dialogConnect.close();
            }
        }
    }

    onDataWifiChanged: {
        //console.log(JSON.stringify(dataWifi));
    }
}
