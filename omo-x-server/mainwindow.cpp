#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, FaceDetector* facedet) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mFaceDetector = facedet;
    connect(mFaceDetector, &FaceDetector::requestStatusUpdate, this, &MainWindow::updateStatusLabel);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

CVImageWidget* MainWindow::getCvImgWidget()
{
    ui->mCVImageWidget->mwidth = ui->mCVImageWidget->width();
    ui->mCVImageWidget->mheight = ui->mCVImageWidget->height();
    return ui->mCVImageWidget;
}

void MainWindow::on_btn_trainFace_clicked()
{
    if (ui->textEdit_name->toPlainText() != "") {
        updateStatusLabel("Place your face int the frame");
        mFaceDetector->requestTrainFace(ui->textEdit_name->toPlainText());
    }
    else
        updateStatusLabel("Input name id");
}

void MainWindow::updateStatusLabel(QString str)
{
    ui->label_status->setText(str);
}

void MainWindow::on_switchCamViews_clicked()
{
    cpRunningOnNetwork = !cpRunningOnNetwork;
    emit changeCamera(cpRunningOnNetwork);
    qDebug("Emitted %d", cpRunningOnNetwork);
}

void MainWindow::on_slider_resolution_sliderMoved(int position)
{
    float factor =  (((float)(100-position) / 100) * 3) + 1;
    if (factor <= 1.04)
        factor = 1;

    ui->label_downsampleF->setText(QStringLiteral("Downsampling Factor: %1").arg(factor));
    emit downsampleFactorChanged(factor);
}

void MainWindow::on_radio_btn_isRGB_clicked(bool checked)
{
    emit isRGBChanged(checked);
}

void MainWindow::on_remote_shutdown_btn_clicked()
{
    emit initiateRemoteShutdown();
}
