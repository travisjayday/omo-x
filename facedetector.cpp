#include "facedetector.h"
#include <QDebug>

FaceDetector::FaceDetector()
{
#ifndef RASPI
    faceClassifier = cv::CascadeClassifier("/home/travis/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml");
#else
    faceClassifier = cv::CascadeClassifier("/home/pi/opencv-3.1.0/data/haarcascades/haarcascade_frontalface_alt2.xml");
#endif
    if (faceClassifier.empty()) {
        qDebug("Failed to load cascade classifier");
    }
}

void FaceDetector::drawFaces(cv::Mat& input) {
    if (skipCounter == 0) {
        skipCounter = 3;
        qDebug("skipping face rec");
    } else {
        skipCounter --;
        cv::Mat gray;
        cv::resize(input, gray, cv::Size(480/4, 480/4));
        cv::cvtColor(gray, gray, cv::COLOR_RGB2GRAY);

        faceClassifier.detectMultiScale(gray, faceVec, 1.1, 3, 0, cv::Size(0, 0), cv::Size(900, 900));
    }

    for (unsigned int i = 0; i < faceVec.size(); i++) {

        //debug rec
        cv::rectangle(input, cv::Rect(faceVec[i].x*4, faceVec[i].y*4, faceVec[i].width*4, faceVec[i].height*4), cv::Scalar(0, 255, 0), 1);

        cv::circle(input, cv::Point(faceVec[i].x*4 + faceVec[i].width/2*4, faceVec[i].y*4 + faceVec[i].height/2*4), faceVec[i].width*2, cv::Scalar(255, 0, 0), 5);
        //move to next circle
    }
}
