#ifndef CVIMAGEWIDGET_H
#define CVIMAGEWIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QPainter>
#include <QPoint>
#include <QImage>
#include <QTimer>
#include "facedetector.h"
#include <QTime>

Q_PROPERTY(bool runningOnNetwork READ runningOnNetwork WRITE setRunningOnNetwork NOTIFY runningOnNetworkChanged);

class CVImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CVImageWidget(QWidget *parent = 0) : QWidget(parent) {
        this->setStyleSheet("background-color: black");
        mwidth = this->width();
        mheight = this->height();
        frameTimer = new QTimer();
        connect(frameTimer, &QTimer::timeout, this, &CVImageWidget::updateFrame);
    }

    ~CVImageWidget() {
        if (cap.isOpened())
            destroyCamera();
    }

    int mwidth;
    int mheight;

public slots:
    void showImage(cv::Mat mat, bool isRGB) {
        cv::Mat gray;
        if (isRGB && mat.type() == CV_8UC3) {
            cv::cvtColor(mat, gray, CV_RGB2GRAY);
        }
        else if (isRGB && mat.type() != CV_8UC3) {
            qDebug("Uh, something went wrong in color");
            return;
        }
        mFaceDetector->drawFaces(isRGB? gray : mat, true);
        mat = paintRes(mat);
        mat = paintBlackBorders(mat);
        QImage finalQimage = QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, isRGB? QImage::Format_RGB888: QImage::Format_Grayscale8);
        imageStack.append(finalQimage);
        repaint();
        frameCnt ++;
        if (showFPS) {
            qDebug("FPS: %d", (float)frameCnt / (fpsTimer.elapsed()*1000));
        }
    }

    bool runningOnNetwork() {
        return mRunningOnNetwork;
    }

    void setRunningOnNetwork(bool param) {
        mRunningOnNetwork = param;
        emit runningOnNetworkChanged(param);
        if (!param) {
            setupCamera(0);
            frameTimer->start(20);
        }
        else {
            destroyCamera();
            frameTimer->stop();
            flushCanvas();
        }
        fpsTimer.start();
    }

    void setFaceDetector(FaceDetector* facedet) {
        mFaceDetector = facedet;
        connect (facedet, &FaceDetector::faceFound, this, &CVImageWidget::faceFound);
    }

    void flushCanvas() {
        QImage img = QImage(this->width(), this->height(), QImage::Format_RGB32);
        img.fill(Qt::gray);
        QPainter p(&img);
        p.setPen(QPen(Qt::black));
        p.setFont(QFont("Times", 20, QFont::Bold));
        p.drawText(img.rect(), Qt::AlignCenter, "No Connection");
        imageStack.clear();
        imageStack.push_back(img);
        flushing = true;
        repaint();
        flushing = false;
    }

signals:
    void runningOnNetworkChanged(bool runningNetwork);
    void faceFound(QString faceData);

protected:
    cv::Mat paintBlackBorders(cv::Mat& frame) {
        int wiheight = this->height();
        int wiwidth = this->width();
        float sf = -1;
        cv::Rect roi;

        if ((float)frame.rows / frame.cols <= (float)wiheight / wiwidth) { //then, black bars go on top/bottom
            sf = (float)wiwidth / frame.cols;
            cv::resize(frame, frame, cv::Size(frame.cols*sf, frame.rows*sf));
            roi = cv::Rect(0, (wiheight- frame.rows) / 2, frame.cols, frame.rows);
        }
        else {
            sf = (float)wiheight / frame.rows;
            cv::resize(frame, frame, cv::Size(frame.cols*sf, frame.rows*sf));
            roi = cv::Rect((wiwidth- frame.cols) / 2, 0 , frame.cols, frame.rows);
        }
        cv::Mat background = cv::Mat(wiheight, wiwidth, frame.channels() == 1? CV_8UC1 : CV_8UC3, cv::Scalar(0, 0, 0));
        frame.copyTo(background(roi));
        return background;
    }

    void resizeEvent(QResizeEvent* /*event*/) {
        mwidth = this->width();
        mheight = this->height();
        if (mRunningOnNetwork)
            flushCanvas();
    }

    void paintEvent(QPaintEvent* /*event*/) {
        // Display the image
        QPainter painter(this);

        if (mRunningOnNetwork || flushing) {
            if (!imageStack.empty()) {
                painter.drawImage(QPoint(0,0), imageStack.last());
                imageStack.pop_back();
            }
        }
        else {
            cv::Mat frame;
            cv::Mat gray;
            cap.read(frame);
            cv::cvtColor(frame, frame, CV_BGR2RGB);
            cv::cvtColor(frame, gray, CV_BGR2GRAY);
            mFaceDetector->drawFaces(frame, false);

            frame = paintRes(frame);
            frame = paintBlackBorders(frame);

            QImage qimg((uchar*)frame.data, frame.cols, frame.rows, (int)frame.step1(), QImage::Format_RGB888);
            painter.drawImage(QPoint(0,0), qimg);
        }

        painter.end();
    }

    cv::Mat paintRes(cv::Mat& frame) {
        cv::putText(frame, std::to_string((int)(frame.cols / mFaceDetector->sampleFactor))
                    + "x" + std::to_string((int)(frame.rows / mFaceDetector->sampleFactor)),
                    cv::Point(0, 20), 0, 0.7, cv::Scalar(0, 0, 255), 2);
        return frame;
    }

    void setupCamera(int id) {
        cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        cap.open(id);
    }

    void destroyCamera() {
        cap.release();
    }

    void updateFrame() {
        repaint();
    }

    QVector<QImage> imageStack;
    int flip = 0;
    cv::Mat _tmp;
    bool mRunningOnNetwork = true;
    cv::VideoCapture cap;
    QTimer* frameTimer;
    FaceDetector* mFaceDetector;
    bool flushing = false;
    bool showFPS = true;
    QTime fpsTimer;
    int frameCnt = 0;
};

#endif // CVIMAGEWIDGET_H
