import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0

import NetworkWireless 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Network Manager")

    Material.accent: Material.color(Material.DeepOrange)
    Material.background: "#f0f0f0"
    Material.foreground: "#333333"

    FontLoader {
        id: material_icon
        source: "qrc:/fonts/MaterialIcons.ttf"
    }

    StackView {
        id: stackview
        anchors.fill: parent
        initialItem: HomePage {}
    }

    NetworkWireless {
        id: wireless
    }
}
