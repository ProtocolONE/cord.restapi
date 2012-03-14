// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.0

Item {
    property alias text: input.text
    property alias maximumLength: input.maximumLength
    anchors.centerIn: parent
    width: 180; height: 28

    TextInput {
        id: input
        color: "#151515"; selectionColor: "green"
        font.pixelSize: 16; font.bold: true
        width: parent.width-16
        anchors.centerIn: parent
        focus: true
    }
}
