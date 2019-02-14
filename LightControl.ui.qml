import QtQuick 2.12
import QtQuick.Controls 2.5
import iotctl.light_control 1.0
import QtQuick.Dialogs 1.3
import QtLocation 5.11

Page {
    id: light_control_page
    width: 600
    height: 400

    title: qsTr("Light Control")

    // TODO(escott) Have this live in the page, not as a dialog
    ColorDialog {
        id: colorDialog
        width: 0
        title: "Please choose a color"
        onAccepted: light_control.color = color
        //onRejected:
        Component.onCompleted: visible = true
        visible: true
    }
    Slider {
        id: brightness_adjust
        x: 200
        y: 319
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        stepSize: 1
        to: 100
        from: 0
        orientation: Qt.Horizontal
        value: 0.5
    }

    LightControl {
        id: light_control
    }

    Connections {
        target: brightness_adjust
        onMoved: light_control.brightness = brightness_adjust.value
    }
}
