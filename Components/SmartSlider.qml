import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Item {
    id: item

    property int position: 0
    property alias _slider: slider
    property int borderRadius: 15
    property int sliderOrientation: Qt.Horizontal
    property int itemWidth: 0
    property int sliderWidth: (sliderOrientation == Qt.Horizontal)? 90 : 60
    property int itemHeight: 0
    property int sliderHeight: (sliderOrientation == Qt.Horizontal)? 60 : 90

    width: (itemWidth > 0)? itemWidth : sliderWidth
    height: (itemHeight > 0)? itemHeight : sliderHeight

    Slider {
        id: slider
        width: sliderWidth
        height: sliderHeight
        anchors.centerIn: parent

        snapMode: Slider.NoSnap
        orientation: sliderOrientation

        background: Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: Material.accent
            radius: borderRadius

            Rectangle {
                id: rectangle_background
                height: (sliderOrientation == Qt.Horizontal)? parent.height : parent.height * parent.parent.position
                width: (sliderOrientation == Qt.Horizontal)? parent.width * parent.parent.position : parent.width
                color: Qt.rgba(Material.accent.r, Material.accent.g, Material.accent.b, slider.position)
                radius: borderRadius

                Component.onCompleted: if (sliderOrientation != Qt.Horizontal) anchors.bottom = parent.bottom
            }
        }
    }
}
