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

    property string _title: qsTr("Configurações da tela")
    property string _icon: "\uE333"

    Component.onCompleted: {
        object.structHeader.push({"title": _title, "icon": _icon});
        headerPage.changePage();
    }

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
                    height: 50

                    _title: qsTr("Brilho")
                    _icon: "\uE8BD"
                    _font: material_icon.name
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
