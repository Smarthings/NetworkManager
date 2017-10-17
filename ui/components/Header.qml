import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Column {
    property int _margin: 20
    property string _title
    property string _icon
    property color _color: Material.foreground
    property var _font
    property int _pixelSize: 22
    property int _iconSize: 32
    property color _line: object.line

    Item {
        width: parent.width
        height: _margin
    }

    RowLayout {
        width: parent.width
        height: 50

        Text {
            text: _icon
            font.family: _font
            font.pixelSize: _iconSize
            color: _color
        }

        Text {
            text: _title
            font.pixelSize: _pixelSize
            Layout.fillWidth: true
            color: _color
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Rectangle {
        width: parent.width
        height: 1
        color: _line
    }
}
