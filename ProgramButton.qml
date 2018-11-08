import QtQuick 2.0

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
    property var currentProgram: "none"
    property variant programs: ["Res/pencil.png", "Res/video.png", "Res/face_rec.png"]
    property int programIdx: 0

    onStateChanged: {
        if (iconPath != "none" && !doOnce)
            buttonIcon.initIcon(iconPath)
        doOnce = true
    }

    id: programButton
    text: "default"
    Layout.alignment: Qt.AlignCenter
    opacity: 0.5
    font.pixelSize: 16
    property var m_pixelSize: programButton.font.pixelSize

    onCurrentProgramChanged: {
        console.log("IDX Changed")
        state = "changePGRM"
        text = currentProgram
        buttonIcon.initIcon(currentProgram)
    }


    background: Rectangle {
        property var m_radius: (root.height + root.width)/2 * 0.3 / 2
        id: tl_backRec
        implicitWidth: (root.height + root.width) / 2 * 0.5
        implicitHeight: (root.height + root.width) / 2 * 0.5
        radius: (root.height + root.width)/2 * 0.3 / 2

        MouseArea {
            z: 5
            id: mArea
            anchors.centerIn: parent
            width: programButton.parent.width / 2
            height: programButton.parent.height / 3
            preventStealing: true
            propagateComposedEvents: true
            hoverEnabled: true
            anchors.fill: parent
            property var yEnter: -1
            property var xEnter: -1

            onEntered: {
                if (containsMouse) {
                    programButton.state = "compressing"
                }
                yEnter = mouseY     //50
                xEnter = mouseX
            }

            onExited: {
                if (!containsMouse) {
                    programButton.state = "idle"
                }
                if (mouseY < yEnter + 20 && mouseY > yEnter - 20 && Math.abs(xEnter - mouseX) > 40 ) {
                    if (xEnter < mouseX)    //Swipe right
                    {
                        programButton.programIdx += 1
                        if (programButton.programIdx > programButton.programs.length -1)
                            programButton.programIdx = 0
                        console.log("Right swipe")
                    }
                    if (xEnter > mouseX) {
                        programButton.programIdx -= 1
                        if (programButton.programIdx < 0)
                            programButton.programIdx = programButton.programs.length-1
                        console.log("Right swipe")

                        console.log("Left swipe")
                    }
                    programButton.currentProgram = programButton.programs[programButton.programIdx]

                    yEnter = -1
                    xEnter = -1
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
                programButton.text = ""
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
                target: programButton
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
                target: programButton
                font.pixelSize: 8
            }
        },
        State {
            name: "changePGRM"
            PropertyChanges {
                target: tl_backRec


            }
        }

    ]

    transitions: [
        Transition {
            id: trans
            reversible: true
            from:  "idle"
            to:"compressing"
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
                    target: programButton
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
        },
        Transition {
            from: "idle"
            to: "changePGRM"
            onRunningChanged: {
                if (programButton.transitions[1].running === false) {
                    programButton.state = "idle"
                }
            }

            SequentialAnimation {

                ParallelAnimation {

                    ColorAnimation {
                        target: tl_backRec
                        duration: 300
                    }
                    NumberAnimation {
                        target: tl_backRec
                        property: "radius"
                        from: tl_backRec.radius
                        to: 0
                        duration: 300
                        easing.type: Easing.InOutQuad
                    }
                    NumberAnimation {
                        target: tl_backRec
                        property: "scale"
                        from: tl_backRec.scale
                        to: 0.1
                        duration: 300
                        easing.type: Easing.InOutQuad
                    }
                    NumberAnimation {
                        target: tl_backRec
                        property: "opacity"
                        from: tl_backRec.opacity
                        to: 0
                        duration: 300
                        easing.type: Easing.OutBack
                    }
                    NumberAnimation {
                        target: buttonIcon
                        property: "opacity"
                        from: 0.5
                        to: 0
                        duration: 50
                        easing.type: Easing.OutBack
                    }
                    NumberAnimation {
                        target: programButton
                        property: "font.pixelSize"
                        from: programButton.font.pixelSize
                        to: 0
                        duration: 300
                        easing.type: Easing.OutBack
                    }
                }
                ParallelAnimation {

                    ColorAnimation {
                        target: tl_backRec
                        duration: 300
                    }
                    NumberAnimation {
                        target: tl_backRec
                        property: "radius"
                        from: 0
                        to: tl_backRec.m_radius
                        duration: 300
                        easing.type: Easing.InOutQuad
                    }
                    NumberAnimation {
                        target: tl_backRec
                        property: "scale"
                        from: 0.1
                        to: 1
                        duration: 300
                        easing.type: Easing.InOutQuad
                    }
                    NumberAnimation {
                        target: tl_backRec
                        property: "opacity"
                        from: 0
                        to: 0.5
                        duration: 300
                        easing.type: Easing.OutBack
                    }
                    NumberAnimation {
                        target: buttonIcon
                        property: "opacity"
                        from: 0
                        to: 1
                        duration: 300
                        easing.type: Easing.OutBack
                    }
                    NumberAnimation {
                        target: programButton
                        property: "font.pixelSize"
                        from: programButton.font.pixelSize
                        to: programButton.m_pixelSize
                        duration: 300
                        easing.type: Easing.OutBack
                    }
                }
            }
        }
    ]
}
