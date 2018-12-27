import QtQuick 2.12
import QtQuick.Controls 2.5
import QtWebSockets 1.1

Rectangle {
    width: 400
    height: 400

    WebSocket {
        id: socket
        url: "ws://localhost:8080/ws"
        property string prevState

        onTextMessageReceived: {
            console.log("received text: " + message);
            const m = JSON.parse(message);
            if (m.gestureState == "STATE_START") {
                ta.text += "投げるよー\n"
            } else if (m.gestureState == "STATE_STOP") {
                if (prevState == "STATE_UPDATE") {
                    ta.text += "投げた！\n"
                }
            }
            prevState = m.gestureState;
        }

        onBinaryMessageReceived: {
            console.log("received binary: " + message.length);
        }

        onStatusChanged: {
            if (socket.status == WebSocket.Error) {
                console.log("error: " + socket.errorString);
            } else if (socket.status == WebSocket.Open) {
                console.log("socket open!");
            } else if (socket.status == WebSocket.Closed) {
                console.log("good bye");
            } else {
                console.log("status changed:"
                    + " Connecting " + (status == WebSocket.Connecting)
                    + " Closing " + (status == WebSocket.Closing));
            }
        }
    }

    Column {
        Row {
            spacing: 48
            Button {
                text: "toggle socket"

                onClicked: {
                    socket.active = !socket.active;
                }
            }

            Button {
                text: "clear"
                onClicked: {
                    ta.text = "";
                }
            }
        }

        TextArea {
            id: ta
            font {
                bold: true
                pointSize: 24
            }
        }
    }
}
