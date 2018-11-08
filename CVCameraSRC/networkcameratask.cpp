#include "networkcameratask.h"
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "BetterVideoCapture.h"
#include <QVideoFrame>
#include <QElapsedTimer>
#include "pointercontroller.h"
#include "transfermatsocket.h"
#include <QQuickWindow>

NetworkCameraTask::NetworkCameraTask(BetterVideoCapture* camera, QVideoFrame* videoFrame,
                       unsigned char* cvImageBuf, int width, int height,
                       bool _fingerDetection, QPoint _winPos, int _programIdx)
{
    this->running = true;
    this->camera = camera;
    this->videoFrame = videoFrame;
    this->cvImageBuf = cvImageBuf;
    this->width = width;
    this->height = height;
    this->fingerDetection = _fingerDetection;
    this->winPos = _winPos;
    this->programIdx = _programIdx;

    face2draw = cv::Rect(-200, -200, 3, 3);

    this->m_pointerController = new PointerController();
    this->client = TransferMatSocket::getInstance();
    client->setCameraTaskWorker(this);

    connect(this, &NetworkCameraTask::requestScreenshot,
            client, &TransferMatSocket::getScreenshot);
}

NetworkCameraTask::~NetworkCameraTask()
{
    //Leave camera and videoFrame alone, they will be destroyed elsewhere
    delete m_pointerController;
}

void NetworkCameraTask::stop()
{
    running = false;
}

void NetworkCameraTask::liveDrawFace(QString msg)
{
    QStringList numbers = msg.split(',');
    qDebug("received message %d", numbers[4].toInt());
    cv::Rect face = cv::Rect(
                numbers[1].toInt(), numbers[2].toInt(),
                numbers[3].toInt(), numbers[4].toInt()
            );
    face2draw = face;
    recognizedName = numbers[5].toStdString();
    drawTimeout = 0;
}

void NetworkCameraTask::receivedScreenshot(QImage img)
{
    qDebug("received screenshot slot");
    winImage = img;
}

void NetworkCameraTask::doWork()
{

#if defined(QT_DEBUG)
    QElapsedTimer timer;
    float fps = 0.0f;
    int millisElapsed = 0;
    int millis;
    timer.start();
#endif

    if(videoFrame)
        videoFrame->map(QAbstractVideoBuffer::ReadOnly);

    cv::Mat screenImage;
    if(videoFrame)
        screenImage = cv::Mat(height,width,CV_8UC4,videoFrame->bits());

    while(running && videoFrame != NULL && camera != NULL){
        if(!camera->grabFrame())
            continue;

        //Get camera image into screen frame buffer
        if(videoFrame){
            cv::Mat tempMat = camera->retrieveFrame();
            if (fingerDetection) {
                detectFinger(tempMat);
            }
            switch (programIdx) {
                case 0: {
                    PGRM_drawing(tempMat);
                    break;
                }
            }

            //tempmat is frame
#ifdef RASPI
            cv::cvtColor(tempMat,screenImage,cv::COLOR_BGR2RGBA);
#else
            cv::cvtColor(tempMat,screenImage,cv::COLOR_RGB2RGBA);
#endif
            if (programIdx == 2) {
                if (drawTimeout < 20) {
                    qDebug("drawingFace");
                    cv::rectangle(screenImage, face2draw, cv::Scalar(255, 0, 0), 3);
                    cv::putText(screenImage, recognizedName, cv::Point(face2draw.x, face2draw.y-20), 0, 2, cv::Scalar(255, 0, 0), 3);
                }
                drawTimeout++;
            }
            //Start Network stuff
            if (client->readyToSendNextFrame) {
                cv::resize(tempMat, tempMat, cv::Size(
                               (int)(tempMat.cols / downSamplingF),
                               (int)(tempMat.rows / downSamplingF))
                           );
                if (!isRgb)
                    cv::cvtColor(tempMat, tempMat, CV_RGB2GRAY);
                else {
                    cv::cvtColor(tempMat, tempMat, CV_RGB2BGR);
                    qDebug("Sending rgb");
                }
                //////////////////////////////////////////////////////

                emit requestScreenshot();
                client->readyToSendNextFrame = false;
            } else {
                emit messageReady("Dropped frame");
            }
        }
        //for physical screen
        emit imageReady();

#if defined(QT_DEBUG)
        millis = (int)timer.restart();
        millisElapsed += millis;
        fps = CAM_FPS_RATE*fps + (1.0f - CAM_FPS_RATE)*(1000.0f/millis);
        if(millisElapsed >= CAM_FPS_PRINT_PERIOD){
            //qDebug("Camera is running at %f FPS",fps);
            millisElapsed = 0;
        }
#endif
    }
}

void NetworkCameraTask::detectFinger(cv::Mat &input) {
    //lower res for better performance & make gray
    qDebug("trying to detect finger");
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_RGB2GRAY);
    cv::resize(gray, gray, cv::Size(width/4, height/4));

  //  cv::Point min_loc, max_loc;
   // double min, max;

    cv::blur(gray, gray, cv::Size(5, 5));
   // cv::minMaxLoc(gray, &min, &max, &min_loc, &max_loc);
   // qDebug() << "min: " << min << "  max: " << max;
  //  if (max > 230) {
        cv::threshold(gray, gray, 200, 255, cv::THRESH_BINARY);
        //imshow("binary", frame);

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;

        cv::findContours(gray, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
        double largestArea = -1;
        int largestContIdx = -1;
        for (unsigned int i = 0; i< contours.size(); i++ ) {// iterate through each contour.
            double a = contourArea(contours[i], false);  //  Find the area of contour
            if (a > largestArea){
                largestArea=a;
                largestContIdx=i;                //Store the index of largest contour
                //try to avoid false detections
                cv::Rect bound = cv::boundingRect(contours[i]);
                if (bound.height < bound.width)
                    largestContIdx = -1;
            }
        }
        if (largestContIdx != -1 && largestArea > 10) { //if contour found
            qDebug("FINGER FOUND");
            cv::Point extTop = *min_element(contours[largestContIdx].begin(), contours[largestContIdx].end(), [](const cv::Point& lhs, const cv::Point& rhs) { return lhs.y < rhs.y; });
            cv::circle(input, extTop*4, 10, cv::Scalar(255, 0, 0), 2);
            cv::line(input, cv::Point(extTop.x - 10, extTop.y)*4, cv::Point(extTop.x+10, extTop.y)*4, cv::Scalar(255, 0, 0), 2);
            cv::Point pos = cv::Point(m_pointerController->getPos().x() + winPos.x(), m_pointerController->getPos().y() + winPos.y());
            //cv::line(input, previousDot, pos, cv::Scalar(255, 0, 0), 2);

            //80 comes from 800 - 640 /2 where. Compensate for border
            m_pointerController->setMousePos(160+winPos.x() + extTop.x*4, winPos.y() + extTop.y*4);
        }
}

void NetworkCameraTask::PGRM_drawing(cv::Mat &input) {
   //rmaps relatively //cv::Point pos = cv::Point(((double) QCursor::pos().x() / (double) 1366) * width,  ((double) QCursor::pos().y() / (double) 768) * height);
    cv::Point pos = cv::Point(QCursor::pos().x() - winPos.x()-160, QCursor::pos().y() - winPos.y());
    previousFingPos.push_back(pos);
    for (uint i = 0; i < previousFingPos.size(); i++)
        cv::circle(input, previousFingPos[i], 5, cv::Scalar(255, 0, 0), -1);
    std::string str = std::to_string(winPos.x()) + ", " + std::to_string(winPos.y());
    cv::putText(input, str, cv::Point(50, 50), 0, 1, cv::Scalar(255, 255, 255), 2);
}
