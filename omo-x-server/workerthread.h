#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include "cvimagewidget.h"

#include <QThread>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "socketserver.h"

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread() {

    }

    void setMat(cv::Mat img) {
        currentImg = img;
        drewNew = false;
    }

    void setWidget(CVImageWidget* wid) {
        widget = wid;
    }

    void run()
    {
        //cv::namedWindow("win");



        while (1) {
         /*   if (server->imageReady) {
                qDebug("in Run from thread, got img");
                //cv::cvtColor(currentImg, currentImg, CV_BGRA2RGB);
                emit imageReady(server->getImage());
                drewNew = true;
            }*/
        }
    }
    cv::Mat currentImg;
    CVImageWidget* widget;
    bool drewNew = false;

signals:
    void imageReady(QImage _img);
};

#endif // WORKERTHREAD_H
