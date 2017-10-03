import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Dialog {
    id: dialog_disconnect

    property string name

    title: qsTr("Desconectar de %1?").arg(name);
    modal: true

    x: Math.round((window.width - width) /2)
    width: 300

    standardButtons: Dialog.No | Dialog.Yes
}
