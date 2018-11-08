import QtQuick 2.4
import QtQuick.Controls 2.0

Item {
    width: 400
    height: 400

    TextArea {
        id: textArea
        x: 56
        y: 97
        width: 216
        height: 137
        text: qsTr("Text Area")
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
    }
}
