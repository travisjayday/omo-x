#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>
#include "loadingdialog.h"


using namespace  std;

class FaceDetector : public QObject
{
    Q_OBJECT
public:
    FaceDetector();
    void drawFaces(cv::Mat input, bool network);
    void requestTrainFace(QString name);
    void saveFaceData(cv::Mat face);

    float sampleFactor = 1;
private:
    cv::CascadeClassifier faceClassifier;
    int skipCounter = 5;
    std::vector<cv::Rect> faceVec;
    bool trainingFace = false;
    QString currentName;
    QString outDir;
    int savedFaceCount = 0;
    int faceSaveSkip = 0;
    cv::Ptr<cv::face::LBPHFaceRecognizer> faceRecognizer;
    bool recognizerTrained = false;
    std::vector<int> faceIds;
    std::vector<QString> faceNames;

    void trainFaceRecognizer();
    int findNumDirs(QString loc);

signals:
    void requestStatusUpdate(QString str);
    void faceFound(QString faceData);
public slots:
    void onDownsampleFactorChanged(float factor);
};

#endif // FACEDETECTOR_H
