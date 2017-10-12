import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import BrightnessManager 1.0

ScrollablePage {
    id: root

    Item {
        width: parent.width
        height: root.height

        Rectangle {
            width: parent.width
            height: root.height
            color: object.background

            Column {
                width: object.width
                height: parent.height
                anchors.centerIn: parent

                Item {
                    width: parent.width
                    height: 10
                }

                RowLayout {
                    width: parent.width
                    height: 50

                    Text {
                        text: "\uE1AE"
                        font.family: material_icon.name
                        font.pixelSize: object.iconTitleSize
                        color: Material.accent
                    }

                    Text {
                        text: qsTr("Altere o brilho da tela")
                        font.pixelSize: object.titleSize
                        Layout.fillWidth: true
                        color: Material.accent
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: object.line
                }

                Item {
                    width: parent.width
                    height: 20
                }

                Item {
                    width: parent.width
                    height: 80

                    Slider {
                        anchors.fill: parent
                        from: 20
                        to: 255
                        value: brightness.brightness

                        snapMode: Slider.NoSnap

                        background: Rectangle {
                            anchors.fill: parent
                            color: "transparent"
                            border.color: Material.accent
                            radius: 5

                            Rectangle {
                                height: parent.height
                                width: parent.width * parent.parent.position
                                color: Material.accent
                                radius: 5
                            }
                        }

                        onValueChanged: brightness.setBrightness(Math.round(value));
                    }
                }
            }
        }

        BrightnessManager {
            id: brightness
        }
    }
}
