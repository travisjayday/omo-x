import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.4
import QtMultimedia 5.0
import com.opencv.qml_camera 2.0
import QtQuick.Controls.Styles 1.4
import QtWebSockets 1.0

ApplicationWindow {
    id: root
    visible: true
    x: 80
    y: 0
    width: 480
    height: 480

    property var firstRender: true

    onAfterRendering: {
        if (firstRender) {
            mouseCursorController.setMousePos(root.width/2, root.height/2)
            hardwareController.switchSingleLed(true)
        }
        firstRender = false
       //  console.log("Url: " + server.url)
    }


    CVCamera2 {
        id: camera
        size: "480x480"
        fingerDetection: true
        winPos: Qt.point(root.x, root.y)
        programIdx: -1
    }

    VideoOutput {
        id: output
        source: camera
        anchors.centerIn: parent
    }

//Point Calibration
    Item {
    id: calibrator
    visible: false
    anchors.fill: parent
    property bool completedPoint: false
    Rectangle {
        width: root.width
        height: root.height
        color: "blue"
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            property int prevMouseX: -1

            onMouseXChanged: {
                if (!calibrator.completedPoint) {
                    root.x = mouseCursorController.getPos().x - root.width /2
                    root.y = mouseCursorController.getPos().y - root.height /2
                } else {
                    if (prevMouseX < mouseX) {
                        //mouse going right
                        root.x += root.width /2
                        root.x += root.height /2
                    } else {
                        root.x -= root.width /2
                        root.x -= root.height /2
                    }

                    root.width = mouseX
                    root.height = mouseX

                }
                finTimer.numTrig = 5
                finTimer.restart()

                timerText.text = 5
            }
            Rectangle {
                id: centerPoint
                width: root.width * 0.1
                height: width
                color: "black"
                radius: root.width * 0.1 /2
                anchors.centerIn: parent
                Text {
                    id: timerText
                    text: "NUM"
                    font.pixelSize: 30
                    color: "white"
                    anchors.centerIn: parent
                }
                  TextArea {
                      id: calibartorCommandTxt
                      text: "By finger gesture, guide the screen \nto center the black point"
                      anchors.bottom: centerPoint.top
                      anchors.horizontalCenter: centerPoint.horizontalCenter
                      font.pixelSize: 15
                      horizontalAlignment: Text.AlignHCenter
                  }
            }
        }
        Timer {
            id: finTimer
            interval: 1000
            repeat: true
            property var numTrig: 5

            onTriggered: {
                if (numTrig == 0 && calibrator.completedPoint) {
                    calibrator.visible = false
                    mainActivity.visible = true
                }
                else if (numTrig == 0 && !calibrator.completedPoint) {
                    calibrator.completedPoint = true
                    numTrig = 5
                    calibartorCommandTxt.text = "Move finger left/right to decrease/increase Zoom."
                }
                    numTrig --
                    camera.size = "480x480"
                    //camera.winPos = Qt.point(root.x, root.y)
                    //camera.update
                    console.log(camera.winPos)
                timerText.text = numTrig
            }
        }
    }
    }


///////////////////////////////////////////////////////////
    Item {
    visible: true
    id: mainActivity
    Rectangle {
        anchors.fill: parent
        id: backRec
    }




    ListView {
        id: rightLeftListView
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        currentIndex: 1
        width: root.width
        height: 0

        model: VisualItemModel {
//Horizontal Item #1
           Rectangle {
                anchors.top: root.top
                width: root.width
                height: root.height
                color: "transparent"

                ProgramButton {
                    id: pgrmBtn
                    anchors.centerIn: parent
                    onClickSentChanged: {
                        camera.programIdx = programIdx
                        camera.size = "480x480"
                        console.log("cliked ", programIdx)
                        if (programIdx == 0) {
                            visible = false
                        }
                    }
                }
                SpecialRoundBtn {
                    text: "BACK"
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.rightMargin: 60
                    onClickSentChanged: {
                        if (clickSent) {
                            if (camera.programIdx != -1) {
                                camera.programIdx = -1
                                camera.size = "480x480"
                                pgrmBtn.visible = true
                            }
                            else {
                                console.log("decrementing");
                                rightLeftListView.incrementCurrentIndex();
                            }
                        }

                    }
                }
            }
//Horizontal Item #2
            Rectangle {
                anchors.top: root.top
                width: root.width
                height: root.height
                color: "transparent"
                ListView {
                    id: pageList
                    snapMode: ListView.SnapOneItem
                    highlightRangeMode: ListView.StrictlyEnforceRange
                    anchors.top: root.top
                    width: 0
                    height: root.height
                    currentIndex: 1

                    onCurrentIndexChanged:  {
                        console.log("change idx is", currentIndex)
                        if (currentIndex === 2) {    //night vision settings on
                            console.log("QML: NIGHT VISION IS ON");
                            hardwareController.switchMultiLed(true);
                        }
                        else {
                            hardwareController.switchMultiLed(false);
                        }
                    }

                    model: VisualItemModel {
                        id: itemModel

            //Vertical Item #1  -- buttons slide down
                        Rectangle {
                            height: root.height;
                            width: root.width;
                            color: "transparent"
                            GridLayout {
                                columns: 2
                                rows: 2
                                width: root.width * 0.8
                                height: root.height -100
                                anchors.centerIn: parent

                                SpecialRoundBtn {
                                    id: tl_btn
                                    text: "Programs"
                                    onClickSentChanged: {
                                        if (clickSent) {
                                            //go left
                                            rightLeftListView.decrementCurrentIndex()
                                        }
                                    }
                                }
                                SpecialRoundBtn {
                                    text: "Settings"
                                    onClickSentChanged: {
                                        if (clickSent) {
                                            //go right
                                            //rightLeftListView.incrementCurrentIndex()
                                        }
                                    }
                                }
                                SpecialRoundBtn {
                                    text: "Help"
                                    onClicked: console.log("the")
                                }
                                SpecialRoundBtn {
                                    text: "Exit"
                                    onClickSentChanged: {
                                        if (clickSent) {
                                            hardwareController.shutdownNow();
                                        }
                                    }
                                }
                            }
                        }
            //Vertical Item #2  -- home screen
                        Rectangle {
                            height: root.height;
                            width: root.width;
                            color: "transparent"

                            Text {
                                anchors.bottom: parent.bottom
                                font.pixelSize: 30
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "OMO-X"
                                color: "white"
                            }

                        }
            //Vertical Item #3  -- night vision
                        Rectangle {
                            height: root.height;
                            width: root.width;
                            color: "green"
                            opacity: 0.2

                        }
                    }


                    Rectangle {
                        x: 160
                        y: root.height / 2 - height / 2
                        width: 70
                        height: 100
                        radius: 35
                        opacity: 0.8

                        Text {
                            text: "⇕"
                            font.pixelSize: 45
                            font.bold: true

                            anchors.centerIn: parent
                        }

                        MouseArea {
                            hoverEnabled: true
                            anchors.fill: parent
                            property var yEnter: -1
                            property var xEnter: -1
                            onEntered: {
                                yEnter = mouseY     //50
                                xEnter = mouseX
                                console.log("entered")
                            }
                            onExited: {
                                if (mouseX < xEnter + 20 && mouseX > xEnter - 20) {
                                    if (yEnter > mouseY)    //Swipe down
                                        pageList.incrementCurrentIndex()
                                    else
                                        pageList.decrementCurrentIndex()
                                    yEnter = -1
                                    xEnter = -1
                                    console.log("Exited")
                                }
                            }
                            focus: true
                        }
                    }
                }
            }
//Horizontal Item #3
/*           Rectangle {
                anchors.top: root.top
                width: root.width
                height: root.height
                color: "red"
            }*/
        }
    }
}
}
