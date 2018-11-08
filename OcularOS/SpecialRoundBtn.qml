import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls 2.0
import QtMultimedia 5.0
import QtQuick.Controls.Styles 1.4


Button {
    property var clickSent: false
    property var doOnce: false
    property var iconPath: "none"
    property var programIdx: "none"

    onStateChanged: {
        if (iconPath != "none" && !doOnce)
            buttonIcon.initIcon(iconPath)
        doOnce = true
    }

    id: tl_btn
    text: "default"
    Layout.alignment: Qt.AlignCenter
    opacity: 0.5
    font.pixelSize: 16

    onProgramIdxChanged: {
        console.log("IDX Changed")
        state: "compressing"

    }

    Rectangle {
        id: mouseRec
        anchors.fill: parent
        color: "transparent"
    }

    background: Rectangle {

        id: tl_backRec
        implicitWidth: (root.height + root.width) / 2 * 0.3
        implicitHeight: (root.height + root.width) / 2 * 0.3
        radius: (root.height + root.width)/2 * 0.3 / 2

        MouseArea {
            z: 5
            id: mArea
            anchors.fill: parent
            preventStealing: true
            propagateComposedEvents: true
            hoverEnabled: true
            onEntered: {
                if (containsMouse) {
                    tl_btn.state = "compressing"

                }
            }
            onExited: {
                if (!containsMouse) {
                    tl_btn.state = "idle"
                }
            }
        }
        Image {
            z: -2
            id: buttonIcon
            function initIcon(path) {
                source = path
                enabled = true
                visible = true
                tl_btn.text = ""
            }

            enabled: false
            visible: false
            source: ""
            anchors.fill: parent
        }
    }
    state: "idle"
    states: [
        State {
            name: "idle"
            PropertyChanges {
                target: tl_backRec
                scale: 1
                radius: (root.height + root.width)/2 * 0.3 / 2
                opacity: 0.5
            }
            PropertyChanges {
                target: tl_btn
                font.pixelSize: 16
            }
        },
        State {
            name: "compressing"
            PropertyChanges {
                target: tl_backRec
                color: "blue"
                radius: 0
                scale: 0
                opacity: 0.3
            }
            PropertyChanges {
                target: tl_btn
                font.pixelSize: 8
            }
        }
    ]

    transitions: [
        Transition {

            ParallelAnimation {

                ColorAnimation {
                    target: tl_backRec
                    duration: 1500
                }
                NumberAnimation {
                    target: tl_backRec
                    property: "radius"
                    duration: 1500
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: tl_backRec
                    property: "scale"
                    duration: 1500
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: tl_backRec
                    property: "opacity"
                    duration: 1500
                    easing.type: Easing.OutBack
                }
                NumberAnimation {
                    target: tl_btn
                    property: "font.pixelSize"
                    duration: 1500
                    easing.type: Easing.OutBack
                }
            }
            onRunningChanged: {
                if (state == "compressing" && !running ) {
                    if (tl_backRec.scale < 0.3)
                        clickSent = true
                    if (programIdx != "none")
                        state = "idle"
                }
            }
        }

    ]
}
