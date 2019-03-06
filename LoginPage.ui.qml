import QtQuick 2.12
import QtQuick.Controls 2.5
import iotctl.login_controller 1.0

Page {
    anchors.fill: parent

    title: qsTr("Login")
    property alias passwordField: passwordField
    property alias loginButton: loginButton

    Label {
        x: 235
        y: 31
        text: "Welcome to iotctl!"
    }

    GroupBox {
        property bool isUserFieldValid: false
        property bool isPasswordFieldValid: false
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
            onEditingFinished: (length > 0) ? groupBox.isUserFieldValid=true: groupBox.isUserFieldValid=false
        }

        TextField {
            id: passwordField
            x: 96
            y: 130
            placeholderText: qsTr("password")
            echoMode: TextInput.Password
            passwordCharacter: "*"
            onEditingFinished: (length > 0) ? groupBox.isPasswordFieldValid=true: groupBox.isPasswordFieldValid=false
        }

        Button {
            id: loginButton
            x: 146
            y: 220
            text: qsTr("Login")
            enabled: groupBox.isUserFieldValid && groupBox.isPasswordFieldValid
        }
    }

    LoginController {
        id: loginController
    }

    Connections {
        target: loginButton
        onClicked: {
            loginController.loginRequested(userTextField.text, passwordField.text)
        }
    }

}






/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
