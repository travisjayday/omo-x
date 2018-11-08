#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include <QObject>
#include <QQuickWindow>
#include "CVCameraSRC/transfermatsocket.h"

class HardwareController : public QObject
{
    Q_OBJECT
public:
    explicit HardwareController(QObject *parent = 0);
    static HardwareController* getInstance() {    if(!instanceFlag) {
            staticInst = new HardwareController();
            instanceFlag = true;
            return staticInst;
        }
        else {
            return staticInst;
        }
    };

    Q_INVOKABLE
    void switchSingleLed(bool on);
    Q_INVOKABLE
    void switchMultiLed(bool on);
    Q_INVOKABLE
    void shutdownNow();
    bool isSingleOn = false;
    bool isMultiOn = false;

private:
    static bool instanceFlag;
    static HardwareController* staticInst;
signals:

public slots:
};

#endif // HARDWARECONTROLLER_H
