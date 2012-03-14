// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.0
import "."
import qGNA.Library 1.0
//AuthManagerViewModel

Rectangle {
	signal onButtonLoginClick()
	signal authRequest(string s)
	signal authLoginChanged(string s)
	signal authPasswordChanged(string s)
    width: 360
    height: 360
    color: "#cf5353"


	AuthManagerViewModel {
		id: authManager
		objectName: "authManager"
		onAuthSuccess: {
			console.log('success');
			console.log('userId ' + authManager.userId); 
			console.log('appKey ' + authManager.appKey);
			resultRect.color = "green";
		}

		onAuthError: {
			console.log('error ');
			console.log(resultCode);
			resultRect.color = "red";
		}
	}

    Rectangle {
		id: resultRect
        x: 278
        y: 241
        width: 69
        height: 86
        color: authModel.backgroundColor
        Text {
            id: name
            color: "#ffffff"
            text: qsTr("text")
        }

        MouseArea {
            x: 0
            y: 0
            width: 321
            height: 201
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.fill: parent
            onClicked: {
				  authManager.login("vkontakte");
            }
//                authManager.login("vkontakte");
        }
    }

    Rectangle {
        id: rectangle1
        x: 279
        y: 65
        width: 68
        height: 31
        color: "#ffffff"

        MouseArea {
            id: mouse_area1
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            onClicked: authManager.login("generic");
        }
    }

    Rectangle {
        x: 30
        y: 15
        width: 217
        height: 31
        border.color: "#000000"
        LineInput {
			onTextChanged : authManager.accountName = loginInput.text;
			id: loginInput
			anchors.centerIn: parent
        }


    }

    Rectangle {
        x: 30
        y: 65
        width: 217
        height: 31
        border.color: "#000000"
        LineInput {
			onTextChanged: authManager.password = passwordInput.text;
            id: passwordInput
            anchors.centerIn: parent
        }
    }

    Text {
        id: text1
        x: 30
        y: 211
        width: 188
        height: 30
        text: authModel.userId
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
    }

}
