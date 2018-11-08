#ifndef NETWORKCAMERATASK_H
#define NETWORKCAMERATASK_H

#include <QObject>
#include <QDebug>
#include "pointercontroller.h"
#include "BetterVideoCapture.h"
#include <QVideoFrame>

class TransferMatSocket;

class NetworkCameraTask : public QObject
{
    Q_OBJECT

public:
    NetworkCameraTask(BetterVideoCapture* camera, QVideoFrame* videoFrame, unsigned char* cvImageBuf, int width, int height,
               bool _fingerDetection, QPoint _winPos, int _programIdx);
    virtual ~NetworkCameraTask();
private:

#if defined(QT_DEBUG)                            //Android camera has its own FPS debug info
    const float CAM_FPS_RATE = 0.9f;            ///< Rate of using the older FPS estimates
    const int CAM_FPS_PRINT_PERIOD = 500;       ///< Period of printing the FPS estimate, in milliseconds
#endif

    int width;                                  ///< Width of the camera image
    int height;                                 ///< Height of the camera image
    BetterVideoCapture* camera;                 ///< The camera to get data from
    bool running = false;                       ///< Whether the worker thread is running
    QVideoFrame* videoFrame;                    ///< Place to draw camera image to
    unsigned char* cvImageBuf;                  ///< Place to export camera image to
    bool fingerDetection = false;
    QPoint winPos;
    int programIdx = 0;
    PointerController* m_pointerController;
    TransferMatSocket* client;
    cv::Rect face2draw;
    std::string recognizedName = "";
    int drawTimeout = 0;
    std::vector<cv::Point> previousFingPos;
    QImage winImage;

    void PGRM_drawing(cv::Mat &input);
    void detectFinger(cv::Mat& input);
public slots:

    /**
     * @brief Continuously gets data from the camera
     */
    void doWork();
    void stop();
    void liveDrawFace(QString msg);
    void receivedScreenshot(QImage img);

signals:

    /**
     * @brief Emitted when image from a new frame is ready
     */
void imageReady();
void byteArrayReady(QByteArray array);
void messageReady(QString msg);
void requestScreenshot();

public:
    float downSamplingF = 1;
    bool isRgb = false;
};


#endif // NETWORKCAMERATASK_H
