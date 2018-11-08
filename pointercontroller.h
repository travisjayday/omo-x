
#ifndef POINTERCONTROLLER_H
#define POINTERCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QQuickImageProvider>
#include <QCursor>
#include <QDebug>

class PointerController : public QObject
{
    Q_OBJECT
public:
    PointerController(QObject * parent = 0) {
        cursor = new QCursor();

    }

    Q_INVOKABLE
    void setMousePos(int gx, int gy)
    {
#ifndef RASPI
        cursor->setPos(gx, gy);
#else
        curLoc = cursor->pos();
        toGo.setX(gx - curLoc.x());
        toGo.setY( gy-curLoc.y());
        QString cmd = QString("echo \"%1 %2 0\" > /sys/devices/platform/virmouse/vmevent").arg(toGo.x()).arg(toGo.y());
        system(cmd.toUtf8().constData());
        //qDebug() << cmd;
        //qDebug() << "current pos: " << curLoc << "goal pos: ( " << gx << ", " << gy << ");" << toGo;
#endif
    }
    Q_INVOKABLE
    QPoint getPos() {
        return cursor->pos();
    }

private:
    QCursor* cursor;
    QPoint toGo;
    QPoint curLoc;

};

#endif // POINTERCONTROLLER_H
