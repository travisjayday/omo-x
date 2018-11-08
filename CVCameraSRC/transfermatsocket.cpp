#include "transfermatsocket.h"
#include "networkcameratask.h"
#include <QWebSocket>
#include <QImage>

//#define HOSTIP "ws://192.168.137.1:4444"
//#define HOSTIP "ws://192.168.0.7:4444"

TransferMatSocket* TransferMatSocket::instance = nullptr;

TransferMatSocket::TransferMatSocket(QObject *parent) : QObject(parent)
{
#ifdef HOSTIP:
    qDebug() << "HOSTIP DEFINED AS ";
    qDebug() << HOSTIP;
#else
    qDebug() << "HOSTIP NOT DEFINED";
#endif
    //setup socket
    qDebug("Attempting to connect to server.");
    reconnectTimer = new QTimer();
    this->client = new QWebSocket();
    connect(client, &QWebSocket::connected,
            this, &TransferMatSocket::onConnected);
    connect(client, &QWebSocket::disconnected, this,
            &TransferMatSocket::onConnectionClosed);
    connect(reconnectTimer, &QTimer::timeout, this, &TransferMatSocket::attemptConnect);
    reconnectTimer->start(2000);
}

TransferMatSocket *TransferMatSocket::getInstance()
{
    if (instance == nullptr) {
            instance = new TransferMatSocket();
        };
    return instance;
}

void TransferMatSocket::setCameraTaskWorker(NetworkCameraTask *task)
{
    connect(task, &NetworkCameraTask::byteArrayReady,
            this, &TransferMatSocket::sendMat);
    connect(task, &NetworkCameraTask::messageReady,
            this, &TransferMatSocket::sendMessageToServer);
    currentTask = task;
}

void TransferMatSocket::onConnected()
{
    qDebug("Connected to server.");
    connect(client, &QWebSocket::textMessageReceived,
            this, &TransferMatSocket::onTextMessageReceived);
    connect(client, &QWebSocket::binaryMessageReceived,
            this, &TransferMatSocket::onBinaryMessageReceived);
    client->sendTextMessage("Hello, server. This is client onConnected.");
    readyToSendNextFrame = true;
    connectedToServer = true;
    reconnectTimer->stop();
}

void TransferMatSocket::onTextMessageReceived(QString msg)
{
    qDebug() << "MESSAGE RECEIVED:: " << msg;
    if (msg == "server: frame received") {
        readyToSendNextFrame = true;
    }
    else if (msg.at(0) == 'F') {
        currentTask->liveDrawFace(msg);
    }
    else if (msg.at(0) == 'S') {        // "Setdownsampling, int"
        float downfactor = msg.split("Set,")[1].toFloat();
        currentTask->downSamplingF = downfactor;
        downSamplingF = downfactor;
    }
    else if (msg.at(0) == 'C') {        // "Color, int"
        bool rgb = msg.split("Color,")[1].toInt();
        currentTask->isRgb = rgb;
        isRgb = rgb;
    }
    else if (msg == "SHUTDOWN") {
        system("shutdown now");
    }
}

void TransferMatSocket::onBinaryMessageReceived(QString msg)
{
    qDebug() << "BINARY RECEIVED:: " << msg;
}

void TransferMatSocket::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "ERROR OCCURED IN CLIENT: " << client->errorString();
    connectedToServer = false;
}

void TransferMatSocket::sendMat(QByteArray array) {
    client->sendBinaryMessage(array);
}

void TransferMatSocket::sendMessageToServer(QString msg)
{
    client->sendTextMessage(msg);
}

void TransferMatSocket::onConnectionClosed()
{
    qDebug("CONNECTION CLOSED...Trying to reconnect");
    if (connectedToServer) {
        reconnectTimer->start(2000);
        connectedToServer = false;
    }
    client->close();
}

void TransferMatSocket::attemptConnect()
{
    if (!connectedToServer) {
        qDebug("Attempting to reconnect");
        client->open(QUrl(HOSTIP));
    }
}
