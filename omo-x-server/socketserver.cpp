#include "socketserver.h"
#include <QDebug>
#include <QWebSocket>
#include <QWebSocketServer>
#include <opencv2/opencv.hpp>

SocketServer::SocketServer(QObject *parent, CVImageWidget* wid) : QObject(parent)
{
    widget = wid;
    server = new QWebSocketServer("myserver", QWebSocketServer::NonSecureMode);
    if (server->listen(QHostAddress::Any, 4444)) {
        qDebug("Listening to port 4444...");
    }
    else {
        qDebug("ERROR in server-listen...");
    }

    connect(server, &QWebSocketServer::newConnection,
            this, &SocketServer::onNewConnection);
    connect(widget, &CVImageWidget::runningOnNetworkChanged,
            this, &SocketServer::onRunningOnNetworkChanged);
    connect(widget, &CVImageWidget::faceFound,
            this, &SocketServer::sendFaceData);
}

QImage SocketServer::getImage()
{
    return finalQimage;
}

void SocketServer::onNewConnection()
{
    qDebug("Client Connnected");
    QWebSocket *pSocket = server->nextPendingConnection();
    client = pSocket;

    connect(pSocket, &QWebSocket::textMessageReceived, this, &SocketServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &SocketServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &SocketServer::socketDisconnected);
    pSocket->sendTextMessage("Thanks for connecting today");
    sessionTime.start();
    clientConnected = true;
}

void SocketServer::processTextMessage(QString message)
{
    qDebug() << "Received: " << message;
    if (message == "Dropped frame") {
        droppedFrames++;
    }
}

void SocketServer::processBinaryMessage(QByteArray array)
{
    client->sendTextMessage("server: frame received");

    if (pauseFrames > 0) {
        pauseFrames --;
        return;
    }


    if (!cpRunningOnNetwork) return;
    cv::Mat currentImg;
    try {
        currentImg = cv::Mat((int)(480/sampleFactor/colorDownsampleF), (int)(480/sampleFactor/colorDownsampleF), colorFormat, array.data());
        qDebug("frame received");

        //QImage(array.data(), 480/sampleFactor/colorDownsampleF, 480/sampleFactor/colorDownsampleF, QImage::Format_Grayscale8)

    }
    catch (exception e) {
        qDebug("EXCEPTION : %s", e.what());
        return;
    }
    widget->showImage(currentImg, colorFormat == CV_8UC3? true : false);

    if (sessionTime.elapsed() > maxSessionTime*1000) {
        //client->close();
    }
}

void SocketServer::socketDisconnected()
{
    qDebug() << "Socket Disconnected... Total frames dropped: " << droppedFrames << "in " << sessionTime.elapsed()/1000;
    qDebug() << "FDPS: " << (float)droppedFrames / (sessionTime.elapsed() / 1000);
    widget->flushCanvas();
    clientConnected = false;
}

void SocketServer::onRunningOnNetworkChanged(bool state)
{
    cpRunningOnNetwork = state;
}

void SocketServer::sendFaceData(QString data)
{
    client->sendTextMessage(data);
}

void SocketServer::onDownsampleFactorChanged(float factor)
{
    sampleFactor = factor;
    pauseFrames = 5;
    if (clientConnected)
        client->sendTextMessage(QStringLiteral("Set,%1").arg(factor*colorDownsampleF));
}

void SocketServer::onRGBChanged(bool isRgb)
{
    colorFormat = isRgb? CV_8UC3 : CV_8UC1;
    pauseFrames = 5;
    if (clientConnected) {
        client->sendTextMessage(QStringLiteral("Color,%1").arg((int)isRgb));
        colorDownsampleF = isRgb? 1.75 : 1;
    }
}

void SocketServer::onInitiateRemoteShutdown()
{
    if (clientConnected) {
        client->sendTextMessage("SHUTDOWN");
    }
}



