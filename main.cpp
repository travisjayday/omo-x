#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

#include "hardwarecontroller.h"
#include "CVCameraSRC/CVCamera.h"
#include <QCursor>
#include <QLoggingCategory>

#include "pointercontroller.h"
#include "CVCameraSRC/transfermatsocket.h"

#define DOWNSAMPLINGFACTOR

int main(int argc, char *argv[])
{
    //load mouse driver
    QLoggingCategory::setFilterRules("*.debug=false");
#ifdef RASPI
qDebug("Raspi is enabled");
system("sudo insmod /home/pi/Downloads/vmMouse/virmouse.ko");
#else
qDebug("raspi NOT defined");
#endif
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QSettings s;
    s.setValue("network_downsampling_factor", 2.00);

    //qml wrapper for moving / getting mouse position
    PointerController* m_cursor = new PointerController();
    //used to manipulate peripherals
    HardwareController* m_hardware = new HardwareController();
    //TransferMatSocket* client = TransferMatSocket::getInstance();

    engine.rootContext()->setContextProperty("mouseCursorController", m_cursor);
    engine.rootContext()->setContextProperty("hardwareController", m_hardware);

    qmlRegisterType<CVCamera>("com.opencv.qml_camera", 2, 0, "CVCamera2");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QQuickWindow* window = qobject_cast<QQuickWindow*>(engine.rootObjects().at(0));

    TransferMatSocket* socketController = TransferMatSocket::getInstance();
    socketController->setParentWindow(window);

    return app.exec();
    delete m_cursor;
    delete m_hardware;
}
