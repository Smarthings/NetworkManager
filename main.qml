import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0
import Qt.labs.settings 1.0

import NetworkManager 1.0
import NetworkWireless 1.0
import NetworkWired 1.0

import "./ui"
import "./ui/dialogs"

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("Configurações")

    Material.accent: Material.color(Material.DeepOrange)
    Material.theme: settings.theme
    Material.background: settings.theme == 0? "#f0f0f0" : "#060606"
    Material.foreground: settings.theme == 0? "#000" : "#f0f0f0"

    QtObject {
        id: object
        property bool busy: false
        property color line: settings.theme == 0? "#ddd" : "#090909"
        property color background: settings.theme == 0? "#fff" : "#000"
        property color foreground: settings.theme == 0? "#333" : "#bbb"
        property int width: (window.width > 400)? 400 : window.width
        property int titleSize: 22
        property int iconTitleSize: 32

        property var structHeader: [
            {"title": "Configurações", "icon": "\uE8B8"}
        ]
        onStructHeaderChanged: {
            headerPage.changePage();
        }
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

    header: HeaderPage {
        id: headerPage
    }

    Rectangle {
        visible: object.busy
        anchors.fill: parent
        color: Qt.rgba(0, 0, 0, 0.8)
        anchors.top: parent.top
        anchors.topMargin: -header.height
        z: 10

        BusyIndicator {
            id: busy_indicator
            anchors.centerIn: parent
        }
        Text {
            width: parent.width
            anchors.top: busy_indicator.bottom
            horizontalAlignment: Text.AlignHCenter

            color: "#fff"
            text: qsTr("aguarde...");
        }

        MouseArea {
            anchors.fill: parent
        }
    }

    Shortcut {
        sequence: "Alt+F4"
        onActivated: {
            window.close();
        }
    }

    HomePage {
        id: homePage
        anchors.fill: parent
    }

    /*homePage.stackview {
        id: homePage.stackview
        anchors.fill: parent
        initialItem: HomePage {}
    }*/

    ToolTip {
        id: message
        timeout: 3000
        topMargin: parent.height
        z: 10
    }

    NetworkManager {
        id: manager
    }

    NetworkWireless {
        id: wireless

        onErrorChanged: {
            message.text = qsTr(error);
            message.visible = true;
        }

        onBusyChanged: {
            object.busy = busyFront;
        }
    }

    NetworkWired {
        id: wired
    }

    DialogTheme {
        id: dialogTheme
    }
}
