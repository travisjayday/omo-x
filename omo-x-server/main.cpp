#include "mainwindow.h"
#include <QApplication>
#include "cvimagewidget.h"
#include "socketserver.h"
#include "workerthread.h"
#include "loadingdialog.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FaceDetector* facedet = new FaceDetector();

    MainWindow* w = new MainWindow(0, facedet);

    CVImageWidget* cvwidget = w->getCvImgWidget();
    cvwidget->setFaceDetector(facedet);
    cvwidget->flushCanvas();
    QObject::connect(w, &MainWindow::changeCamera, cvwidget, &CVImageWidget::setRunningOnNetwork);
    SocketServer* server = new SocketServer(0, cvwidget);

    QObject::connect(w, &MainWindow::downsampleFactorChanged, server, &SocketServer::onDownsampleFactorChanged);
    QObject::connect(w, &MainWindow::downsampleFactorChanged, facedet, &FaceDetector::onDownsampleFactorChanged);
    QObject::connect(w, &MainWindow::isRGBChanged, server, &SocketServer::onRGBChanged);
    QObject::connect(w, &MainWindow::initiateRemoteShutdown, server, &SocketServer::onInitiateRemoteShutdown);

    w->show();

    return a.exec();
}
