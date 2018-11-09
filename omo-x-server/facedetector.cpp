#include "facedetector.h"
#include <QDebug>
#include <windows.h>
#include <string>
#include <fstream>
#include <QDir>

//#define USERFILE "C:\\Users\\Travis\\Documents\\QtProjects\\WidgetsProcessor\\faces\\users.txt"
//#define USERDIR "C:\\Users\\Travis\\Documents\\QtProjects\\WidgetsProcessor\\faces\\"

#define USERFILE "D:\\User\\Travis\\Documents\\Programming\\Qt\\omo-x\\omo-x-server\\faces\\users.txt"
#define USERDIR "D:\\User\\Travis\\Documents\\Programming\\Qt\\omo-x\\omo-x-server\\faces\\"
#define TRAININGSET_SIZE 40

FaceDetector::FaceDetector()
{
    faceClassifier = cv::CascadeClassifier("D:\\User\\Travis\\Documents\\Libraries\\OpenCV-3.2.0\\opencv-master\\build\\install\\etc\\haarcascades\\haarcascade_frontalface_default.xml");
    if (faceClassifier.empty()) {
        qDebug("Failed to load cascade classifier");
    }
    faceVec.clear();
    faceRecognizer = cv::face::createLBPHFaceRecognizer();
    if (findNumDirs(USERDIR) > 0) {
        trainFaceRecognizer();
    }
}

void FaceDetector::drawFaces(cv::Mat input, bool network) {
    cv::Mat gray;
    cv::resize(input, gray, cv::Size(input.cols/sampleFactor, input.rows/sampleFactor));
    if (input.type() != CV_8UC1) {
        qDebug("Warning: Converting input image to gray in face detector");
        cv::cvtColor(input, gray, CV_BGR2GRAY);
    }
    if (skipCounter == 0) {
        skipCounter = 3;
        qDebug("skipping face detection");
    }
    else {
        skipCounter --;

        faceClassifier.detectMultiScale(gray, faceVec, 1.1, 3, 0, cv::Size(0, 0), cv::Size(900, 900));
    }

    for (unsigned int i = 0; i < faceVec.size(); i++) {

        //debug rec
        cv::rectangle(input, cv::Rect(faceVec[i].x*sampleFactor, faceVec[i].y*sampleFactor, faceVec[i].width*sampleFactor, faceVec[i].height*sampleFactor), cv::Scalar(0, 255, 0), 1);
        //cv::rectangle(gray, cv::Rect(faceVec[i].x, faceVec[i].y, faceVec[i].width, faceVec[i].height), cv::Scalar(0, 255, 0), 5);
        //cv::circle(input, cv::Point(faceVec[i].x*sampleFactor + faceVec[i].width/2*sampleFactor, faceVec[i].y*sampleFactor + faceVec[i].height/2*sampleFactor), faceVec[i].width*2, cv::Scalar(255, 0, 0), 5);
        //move to next circle
        if (recognizerTrained && !trainingFace && faceVec.size() == 1) {
            qDebug("Predicting facee");
            int predictedFace;
            double confidence;
            cv::Mat face = gray(faceVec[0]);
            cv::resize(face, face, cv::Size(100, 100));
            if (face.isContinuous()) {
                faceRecognizer->predict(face,
                        predictedFace, confidence);
                if (predictedFace >= 0) {
                    qDebug("Found index: %d with name %s", predictedFace, qUtf8Printable(faceNames[predictedFace]));

                    emit requestStatusUpdate(
                                QStringLiteral("Face found %1, with %2 confidence").arg(
                                    qUtf8Printable(faceNames[predictedFace]),  QString::number(confidence)));

                    if (network) {
                        QString message = QStringLiteral("FACE,%1,%2,%3,%4,%5").arg(
                                QString::number((int)(faceVec[i].x*sampleFactor*sampleFactor)), QString::number((int)(faceVec[i].y*sampleFactor*sampleFactor)),
                                QString::number((int)(faceVec[i].width*sampleFactor*sampleFactor)), QString::number((int)(faceVec[i].height*sampleFactor*sampleFactor)),
                                qUtf8Printable(faceNames[predictedFace]));
                         emit faceFound(message);
                    }

                    cv::putText(input, faceNames[predictedFace].toStdString(), cv::Point(faceVec[i].x*sampleFactor, faceVec[i].y*sampleFactor), CV_FONT_HERSHEY_PLAIN, sampleFactor + 0.5, cv::Scalar(0, 255, 0), 1);
                }
                else {
                    qDebug("Could not predict face");
                }
            }
            else {
                qDebug("STOPPED CONTINOUS ERROR");
            }
        }
    }

    if (trainingFace) {
        if (faceSaveSkip == 6) {
            faceSaveSkip = 0;
            qDebug("Commencing to save face");
            if (faceVec.size() == 1) {              //good
                emit requestStatusUpdate(QStringLiteral("Training... %1 / %2").arg(savedFaceCount, TRAININGSET_SIZE-1));
                //write images to file
                saveFaceData(gray(faceVec[0]));
            }
            else if (faceVec.size() == 0) {         //not enough face
                emit requestStatusUpdate("Place face in screen frame");
            }
            else {                                  //too many faces
                emit requestStatusUpdate("Too many faces");
            }
        }
        else {
            qDebug("Skipped commencing to save face");
            faceSaveSkip++;
        }
    }
}

void FaceDetector::requestTrainFace(QString name)
{
    currentName = name.trimmed();
    trainingFace = true;
    qDebug("Creating output directory");
    outDir = USERDIR + currentName;

    if (QDir().exists(outDir)? 0 : QDir().mkdir(outDir)) {
        // Directory created
        qDebug("Dir created succesfully");
    }
    else {
        // Failed for some other reason
        qDebug("Directory already exists");
        emit requestStatusUpdate("User already exists...");
        trainingFace = false;
        return;
    }
   /* //creates users file
    ofstream usrFile;
    usrFile.open(USERFILE, ios::out | ios::app);
    usrFile << name.toStdString() << "\n";
    usrFile.close();*/

    QFile usrFile(USERFILE);
    usrFile.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&usrFile);
    stream << currentName << "\n";
    usrFile.close();
}

void FaceDetector::saveFaceData(cv::Mat face) {
    qDebug("Writing to output file");
    cv::resize(face, face, cv::Size(100, 100));
    cv::imwrite(outDir.toStdString() + "\\" + std::to_string(savedFaceCount) + currentName.toStdString() + ".png", face);
    savedFaceCount++;
    if (savedFaceCount > TRAININGSET_SIZE-1) {
        requestStatusUpdate("Finished");
        trainingFace = false;
        savedFaceCount = 0;
        faceSaveSkip = 0;
        trainFaceRecognizer();
    }

}

void FaceDetector::trainFaceRecognizer()
{
    std::vector<cv::Mat> faces;
    faceIds.clear();
    faceNames.clear();
    QFile usrFile(USERFILE);

    LoadingDialog* loader = new LoadingDialog();
    loader->show();

    int i = 0;
    usrFile.open(QIODevice::Text | QIODevice::ReadOnly);
    while (!usrFile.atEnd()) {
        QString name = usrFile.readLine().trimmed();
        qDebug(name.toStdString().c_str());
        if (name.length() <= 1) {
            break;
        }
        int faceImgs = findNumDirs(USERDIR + name + "\\");
        for (int x = 0; x < faceImgs; x++) {
            cv::Mat fac = cv::imread(USERDIR + name.toStdString() + "\\" + std::to_string(x) + name.toStdString() + ".png", 0);
            if (!fac.empty()) {
                faces.push_back(fac);
                faceIds.push_back(i);
            }
            else {
                qDebug("ERROR Reading face file...");
            }
        }

        faceNames.push_back(name);
        i++;

    }
    qDebug("faceids size: %d, faces size: %d", faceIds.size(), faces.size());

    faceRecognizer->train(faces, faceIds);
    recognizerTrained = true;
    loader->close();
}

int FaceDetector::findNumDirs(QString loc) {
    QDir dir(loc);
    dir.setFilter( QDir::Files );
    int cnt = dir.count();
    qDebug("Found %d file in %s", cnt, qUtf8Printable(loc));
    return cnt;
}

void FaceDetector::onDownsampleFactorChanged(float factor)
{
    sampleFactor = factor;
}


