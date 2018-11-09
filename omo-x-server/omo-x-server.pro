#-------------------------------------------------
#
# Project created by QtCreator 2017-02-12T13:40:47
#
#-------------------------------------------------

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = omo-x-server
TEMPLATE = app

INCLUDEPATH += D:/User/Travis/Documents/Libraries/OpenCV-3.2.0/opencv-master/build/install/include \

CONFIG(debug, debug|release) {
LIBS += -LD:/User/Travis/Documents/Libraries/OpenCV-3.2.0/opencv-master/build/install/x64/vc14/lib \
    -lopencv_core320d \
    -lopencv_face320d \
    -lopencv_imgproc320d \
    -lopencv_highgui320d \
    -lopencv_objdetect320d \
    -lopencv_imgcodecs320d \
    -lopencv_video320d \
    -lopencv_videoio320d
}

CONFIG(release, debug|release) {
LIBS += -LD:/User/Travis/Documents/Libraries/OpenCV-3.2.0/opencv-master/build/install/x64/vc14/lib \
    -lopencv_core320 \
    -lopencv_face320 \
    -lopencv_imgproc320 \
    -lopencv_highgui320 \
    -lopencv_objdetect320 \
    -lopencv_imgcodecs320 \
    -lopencv_video320 \
    -lopencv_videoio320
}





# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp\
        socketserver.cpp\
        facedetector.cpp \
    loadingdialog.cpp

HEADERS  += mainwindow.h\
        workerthread.h\
        socketserver.h\
        cvimagewidget.h\
        facedetector.h \
    loadingdialog.h


FORMS    += mainwindow.ui \
    loadingdialog.ui
