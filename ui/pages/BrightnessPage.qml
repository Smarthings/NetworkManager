import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import BrightnessManager 1.0

import "../"
import "../dialogs"
import "../components"

ScrollablePage {
    id: root

    Item {
        width: parent.width
        height: root.height

        Rectangle {
            width: parent.width
            height: root.height
            color: object.background

            ColumnLayout {
                width: object.width
                height: parent.height
                anchors.centerIn: parent

                Header {
                    width: parent.width

                    _title: qsTr("Altere o brilho da tela")
                    _icon: "\uE1AE"
                    _font: material_icon.name
                }

                Item {
                    width: parent.width
                    height: 20
                }

                Item {
                    width: parent.width
                    Layout.fillHeight: true

                    SmartSlider {
                        itemHeight: 100
                        itemWidth: parent.width
                        sliderWidth: parent.width -10

                        _slider.to: 255
                        _slider.from: 20
                        _slider.value: brightness.brightness

                        _slider.onValueChanged: brightness.setBrightness(Math.round(_slider.value));
                    }
                }
            }
        }

        BrightnessManager {
            id: brightness
        }
    }
}
