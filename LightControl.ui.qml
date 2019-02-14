import QtQuick 2.12
import QtQuick.Controls 2.5
import iotctl.light_control 1.0

Page {
    id: light_control_page
    width: 600
    height: 400

    title: qsTr("Light Control")

    Slider {
        id: brightness_adjust
        x: 200
        y: 319
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
