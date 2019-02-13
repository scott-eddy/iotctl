import QtQuick 2.12
import QtQuick.Controls 2.5
import iotctl.light_control 1.0

Page {
    width: 600
    height: 400

    title: qsTr("Page 1")

    Slider {
        id: slider
        x: 200
        y: 319
        orientation: Qt.Horizontal
        value: 0.5
    }

    LightControl {
       id: light_control
    }

    Connections {
        target: slider
        onMoved: light_control.brightness = slider.value
    }
}
