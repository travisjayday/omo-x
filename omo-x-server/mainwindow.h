#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cvimagewidget.h"
#include "facedetector.h"

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, FaceDetector* facedet = 0);
    ~MainWindow();
    CVImageWidget* getCvImgWidget();

private slots:
    void on_btn_trainFace_clicked();
    void updateStatusLabel(QString str);
    void on_switchCamViews_clicked();
    void on_slider_resolution_sliderMoved(int position);

    void on_radio_btn_isRGB_clicked(bool checked);

    void on_remote_shutdown_btn_clicked();

signals:
    void changeCamera(bool runningOnNetwork);
    void downsampleFactorChanged(float factor);
    void isRGBChanged(bool isRgb);
    void initiateRemoteShutdown();

private:
    Ui::MainWindow *ui;
    FaceDetector* mFaceDetector;
    bool cpRunningOnNetwork = true;
    bool localCamFront = true;
};

#endif // MAINWINDOW_H
