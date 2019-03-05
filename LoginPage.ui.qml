import QtQuick 2.12
import QtQuick.Controls 2.5
import iotctl.login_controller 1.0

Page {
    anchors.fill: parent

    title: qsTr("Login")

    Label {
        x: 235
        y: 31
        text: "Welcome to iotctl!"
    }

    GroupBox {
        id: groupBox
        x: 112
        y: 68
        width: 416
        height: 345
        title: qsTr("Login")

        TextField {
            id: userTextField
            x: 96
            y: 47
            placeholderText: qsTr("user")
        }

        TextField {
            id: passwordField
            x: 96
            y: 130
            placeholderText: qsTr("password")
            echoMode: TextInput.Password
            passwordCharacter: "*"
        }

        Button {
            id: loginButton
            x: 146
            y: 220
            text: qsTr("Login")
        }
    }

    LoginController {
        id: loginController
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
