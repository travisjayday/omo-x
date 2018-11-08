#ifndef TRANSFERMATSOCKET_H
#define TRANSFERMATSOCKET_H

#include <QObject>
#include <QDebug>
#include <QWebSocket>
#include <CVCameraSRC/networkcameratask.h>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <QQuickWindow>
#include <QImage>

class TransferMatSocket : public QObject
{
    Q_OBJECT

public:
    explicit TransferMatSocket(QObject *parent = 0);
    static TransferMatSocket* getInstance();
    void setCameraTaskWorker(NetworkCameraTask* task);
    void setParentWindow(QQuickWindow* win) {
        window = win;
        qDebug("set qwindow");
    }
    QQuickWindow* getParentWindow() {
        if (window != nullptr) {
            return window;
        }
        qDebug("Error occurred. Window is not initialized");
        return nullptr;
    }

    bool readyToSendNextFrame = false;
    QQuickWindow* window;

private:
    QWebSocket* client;
    static TransferMatSocket* instance;
    QTimer* reconnectTimer;
    bool connectedToServer = false;
    NetworkCameraTask* currentTask;
    float downSamplingF = 1;
    bool isRgb = false;

public slots:
    void onConnected();
    void onTextMessageReceived(QString msg);
    void onBinaryMessageReceived(QString msg);
    void onError(QAbstractSocket::SocketError error);
    void sendMat(QByteArray array);
    void sendMessageToServer(QString msg);
    void onConnectionClosed();
    void attemptConnect();
    void getScreenshot() {
        QImage winImage = window->grabWindow();
        if (isRgb)
            winImage = winImage.convertToFormat(QImage::Format_RGB888);
        else
            winImage = winImage.convertToFormat(QImage::Format_Grayscale8);

        cv::Mat tempMat = cv::Mat(winImage.height(), winImage.width(),
                                  isRgb? CV_8UC3 : CV_8UC1, winImage.bits(), winImage.bytesPerLine());

#ifdef RASPI
        tempMat = tempMat(cv::Rect(160, 0, 480, 480));
        qDebug() << "size: " << tempMat.cols << "x" << tempMat.rows;
#endif
        cv::resize(tempMat, tempMat, cv::Size(
                       (int)(tempMat.cols / downSamplingF),
                       (int)(tempMat.rows / downSamplingF))
                   );


        size_t sizeofMat = tempMat.step[0] * tempMat.rows;
        qDebug() << sizeofMat << " | " << tempMat.type();
        QByteArray byteArray((char*)(tempMat.data), (int)sizeofMat);


        //QByteArray byteArray((char*)winImage.bits(),winImage.byteCount());
      /*  qDebug() << "Image size: " << winImage.width() << "x" << winImage.height() <<
                    "QByteArray size: " << byteArray.size()
                    << "  Img format: " << winImage.format();*/
        sendMat(byteArray);
    }
};

#endif // TRANSFERMATSOCKET_H
