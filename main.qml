import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0
import Qt.labs.settings 1.0

import NetworkWireless 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Network Manager")

    Material.accent: Material.color(Material.DeepOrange)
    Material.theme: settings.theme
    Material.background: settings.theme == 0? "#f0f0f0" : "#111111"
    Material.foreground: settings.theme == 0? "#111111" : "#f0f0f0"

    QtObject {
        id: object

        property color line: settings.theme == 0? "#ddd" : "#2f2f2f"
    }

    Settings {
        id: settings
        property int theme: 0

        onThemeChanged: {
            Material.theme = settings.theme
        }
    }

    FontLoader {
        id: material_icon
        source: "qrc:/fonts/MaterialIcons.ttf"
    }

    header: Rectangle {
        id: headerPage
        width: window.width
        height: 50
        color: "transparent"

        RowLayout {
            anchors.fill: parent
            spacing: 5

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "transparent"

                RowLayout {
                    id: item_text
                    anchors.fill: parent
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    spacing: 5

                    Text {
                        width: 30
                        text: wireless.wifi_connected === "off/any"? "\uE8A9" : "\uE1BA"
                        font.family: material_icon.name
                        color: "#999"
                    }

                    Text {
                        text: wireless.wifi_connected === "off/any"? qsTr("Sem conexão") : qsTr("Conectado à %1").arg(wireless.wifi_connected)
                        Layout.fillWidth: true
                        color: "#999"
                    }
                }
            }

            Rectangle {
                Layout.fillHeight: true
                width: 50
                color: "transparent"

                ToolButton {
                    id: buttonStyle
                    text: "\uE243"
                    font.family: material_icon.name
                    onClicked: {
                        dialogTheme.dialog.open()
                    }
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 1
            color: object.line
            anchors.bottom: parent.bottom
        }
    }

    Shortcut {
        sequence: "Alt+F4"
        onActivated: {
            window.close();
        }
    }

    StackView {
        id: stackview
        anchors.fill: parent
        initialItem: HomePage {}
    }

    ToolTip {
        id: message
        timeout: 3000
        topMargin: parent.height
        z: 3
    }

    NetworkWireless {
        id: wireless

        onErrorChanged: {
            message.text = qsTr(error);
            message.visible = true;
        }
    }

    DialogTheme {
        id: dialogTheme
    }
}
