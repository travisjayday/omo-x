QT += qml quick websockets multimedia

CONFIG += c++11 release

SOURCES += main.cpp \
    hardwarecontroller.cpp \
    CVCameraSRC/BetterVideoCapture.cpp \
    CVCameraSRC/CameraThread.cpp \
    CVCameraSRC/CVCamera.cpp \
    facedetector.cpp \
    CVCameraSRC/transfermatsocket.cpp \
    CVCameraSRC/networkcameratask.cpp

HEADERS += \
    pointercontroller.h \
    hardwarecontroller.h \
    CVCameraSRC/BetterVideoCapture.h \
    CVCameraSRC/CameraThread.h \
    CVCameraSRC/CVCamera.h \
    facedetector.h \
    CVCameraSRC/transfermatsocket.h \
    CVCameraSRC/networkcameratask.h

RESOURCES += \
    qml.qrc

INCLUDEPATH += /usr/local/lib
LIBS += `pkg-config --static --cflags --libs opencv` -lraspicam_cv -lraspicam -lX11

#If deploying on Raspebrry Pi, uncomment this
DEFINES += RASPI

# computer IP for client
DEFINES += HOSTIP=\\\"ws://192.168.137.1:4444\\\"

# Additional import path used to resolve QML modues in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt QuickDesigner
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS +=

DISTFILES += \
    TestuiForm.ui.qml \
    Testui.qml
