#include "hardwarecontroller.h"
#include <QDebug>

HardwareController::HardwareController(QObject *parent) : QObject(parent)
{
    //issue gpio setup mode commands here
    qDebug() << "Setting GPIO 3 & 4 as OUT";

    system("gpio mode 3 out");
    system("gpio mode 4 out");
}

void HardwareController::switchSingleLed(bool on) {
    if (on) {
        qDebug() << "Setting GPIO 3 HI";
        system("gpio write 3 1");
    }
    else {
        qDebug() << "Setting GPIO 3 LOW";
        system("gpio write 3 0");
    }
    isSingleOn = on;
}

void HardwareController::switchMultiLed(bool on) {
    if (on) {
        qDebug() << "Setting GPIO 4 HI";
        system("gpio write 4 1");
    }
    else {
        qDebug() << "Setting GPIO 4 LOW";
        system("gpio write 4 0");
    }
    isMultiOn = on;
}

void HardwareController::shutdownNow()
{
    system("shutdown now");
}
