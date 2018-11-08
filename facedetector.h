#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <opencv2/opencv.hpp>

class FaceDetector
{
public:
    FaceDetector();
    void drawFaces(cv::Mat& input);
private:
    cv::CascadeClassifier faceClassifier;
    int skipCounter = 5;
    std::vector<cv::Rect> faceVec;
};

#endif // FACEDETECTOR_H
