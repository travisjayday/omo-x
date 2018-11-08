 /*
 * Copyright (C) 2014 EPFL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

/**
 * @file CameraThread.cpp
 * @brief Listens to the camera in a separate thread
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2014-09-23
 */
#define QT_DEBUG
#include"CameraThread.h"
#include <QCursor>
#include "networkcameratask.h"

//*****************************************************************************
// CameraTask implementation
//*****************************************************************************

CameraTask::CameraTask(BetterVideoCapture* camera, QVideoFrame* videoFrame,
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

    for (int i = 0; i < maxPrevPosSize; i++) {
        previousPos.push_back(cv::Point(0, 0));
    }

    this->m_pointerController = new PointerController();
    this->m_faceDetector = new FaceDetector();
}

CameraTask::~CameraTask()
{
    //Leave camera and videoFrame alone, they will be destroyed elsewhere
    delete m_pointerController;
}

void CameraTask::stop()
{
    running = false;
}

void CameraTask::convertUVsp2UVp(unsigned char* __restrict srcptr, unsigned char* __restrict dstptr, int stride)
{
    for(int i=0;i<stride;i++){
        dstptr[i]           = srcptr[i*2];
        dstptr[i + stride]  = srcptr[i*2 + 1];
    }
}

void CameraTask::doWork()
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
        //unsigned char* cameraFrame =

        //Get camera image into screen frame buffer
        if(videoFrame){
            cv::Mat tempMat = camera->retrieveFrame();


            //DO IMAGE PROCESSING
            if (fingerDetection) {
                detectFinger(tempMat);
            }
            switch (programIdx) {
                case 0:
                    PGRM_drawing(tempMat);
                    break;
                case 2:
                    m_faceDetector->drawFaces(tempMat);
            }
#ifdef RASPI
            cv::cvtColor(tempMat,screenImage,cv::COLOR_BGR2RGBA);
#else
            cv::cvtColor(tempMat,screenImage,cv::COLOR_RGB2RGBA);
#endif
        }

        emit imageReady();

#if defined(QT_DEBUG)
        millis = (int)timer.restart();
        millisElapsed += millis;
        fps = CAM_FPS_RATE*fps + (1.0f - CAM_FPS_RATE)*(1000.0f/millis);
        if(millisElapsed >= CAM_FPS_PRINT_PERIOD){
            qDebug("Camera is running at %f FPS",fps);
            millisElapsed = 0;
        }
#endif

    }
}

void CameraTask::detectFinger(cv::Mat &input) {
    //lower res for better performance & make gray
    qDebug("finger trying");
    cv::Mat gray;
    cv::resize(input, gray, cv::Size(width/4, height/4));
    cv::cvtColor(gray, gray, cv::COLOR_RGB2GRAY);

    cv::Point min_loc, max_loc;
    double min, max;

    cv::blur(gray, gray, cv::Size(10, 10));
    cv::minMaxLoc(gray, &min, &max, &min_loc, &max_loc);
   // qDebug() << "min: " << min << "  max: " << max;
    if (max > 230) {
        cv::threshold(gray, gray, max-10, max, cv::THRESH_BINARY);
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
        if (largestContIdx != -1 && largestArea > 30) { //if contour found
            qDebug("FINGER FOUND");
            cv::Point extTop = *min_element(contours[largestContIdx].begin(), contours[largestContIdx].end(), [](const cv::Point& lhs, const cv::Point& rhs) { return lhs.y < rhs.y; });
            cv::circle(input, extTop*4, 10, cv::Scalar(255, 0, 0), 2);
            cv::line(input, cv::Point(extTop.x - 10, extTop.y)*4, cv::Point(extTop.x+10, extTop.y)*4, cv::Scalar(255, 0, 0), 2);
            cv::Point pos = cv::Point(m_pointerController->getPos().x() + winPos.x(), m_pointerController->getPos().y() + winPos.y());
            cv::line(input, previousDot, pos, cv::Scalar(255, 0, 0), 2);
            previousDot = pos;

            previousPos[currentPos] = extTop * 4;
            currentPos++;
            if (currentPos > maxPrevPosSize -1) {
                currentPos = 0;
            }
            int sumX = 0;
            int sumY = 0;
            foreach(cv::Point pnt, previousPos) {
                sumX += pnt.x;
                sumY += pnt.y;
            }
            //80 comes from 800 - 640 /2 where
            m_pointerController->setMousePos(160+winPos.x() + sumX/previousPos.size(), winPos.y() + sumY/previousPos.size());
        }
    }
}

void CameraTask::PGRM_drawing(cv::Mat &input) {
   //rmaps relatively //cv::Point pos = cv::Point(((double) QCursor::pos().x() / (double) 1366) * width,  ((double) QCursor::pos().y() / (double) 768) * height);
    cv::Point pos = cv::Point(QCursor::pos().x() - winPos.x()-160, QCursor::pos().y() - winPos.y());
    previousFingPos.push_back(pos);
    for (uint i = 0; i < previousFingPos.size(); i++)
        cv::circle(input, previousFingPos[i], 5, cv::Scalar(255, 0, 0), -1);
    std::string str = std::to_string(winPos.x()) + ", " + std::to_string(winPos.y());
    cv::putText(input, str, cv::Point(50, 50), 0, 1, cv::Scalar(255, 255, 255), 2);
}



//*****************************************************************************
// CameraThread implementation
//*****************************************************************************

CameraThread::CameraThread(BetterVideoCapture* camera, QVideoFrame* videoFrame,
                           unsigned char* cvImageBuf, int width, int height,
                           bool _fingerDetection, QPoint _winPos, int _programIdx)
{
    task = new NetworkCameraTask(camera,videoFrame,cvImageBuf,width,height,_fingerDetection, _winPos, _programIdx);
    task->moveToThread(&workerThread);
    connect(&workerThread, SIGNAL(started()), task, SLOT(doWork()));
    connect(task, SIGNAL(imageReady()), this, SIGNAL(imageReady()));
}

CameraThread::~CameraThread()
{
    stop();
    delete task;
}

void CameraThread::start()
{
    workerThread.start();
}

void CameraThread::stop()
{
    if(task != NULL)
        task->stop();
    workerThread.quit();
    workerThread.wait();
}

