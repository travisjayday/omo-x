#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <opencv2/opencv.hpp>
#include "cvimagewidget.h"
#include "facedetector.h"

class SocketServer : public QObject
{
    Q_OBJECT
public:
    explicit SocketServer(QObject *parent = 0, CVImageWidget* widget = 0);
    QImage getImage();
    bool imageReady = false;
signals:

public slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray data);
    void socketDisconnected();
    void onRunningOnNetworkChanged(bool state);
    void sendFaceData(QString data);
    void onDownsampleFactorChanged(float factor);
    void onRGBChanged(bool isRgb);
    void onInitiateRemoteShutdown();

private:
    QWebSocketServer *server;
    bool clientConnected = false;
    CVImageWidget* widget;
    QImage Mat2QImage(cv::Mat const& src);
    QImage finalQimage;
    QWebSocket* client;
    int droppedFrames = 0;
    QTime sessionTime;
    int maxSessionTime = 55; //seconds
    FaceDetector* mFaceDetector;
    bool cpRunningOnNetwork = true;
    float sampleFactor = 1;
    int colorFormat = CV_8UC1;
    int colorDownsampleF = 1;
    int pauseFrames = 0;

};

#endif // SOCKETSERVER_H
