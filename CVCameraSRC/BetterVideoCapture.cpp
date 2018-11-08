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
 * @file BetterVideoCapture.cpp
 * @brief A wrapper for either cv::VideoCapture for desktop or CVCaptureAndroid for Android
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2014-10-02
 */

#include"BetterVideoCapture.h"
#include <QDebug>
#include <QString>

BetterVideoCapture::BetterVideoCapture()
{
#ifndef RASPI
    capture = new cv::VideoCapture();
#endif
}

BetterVideoCapture::~BetterVideoCapture()
{
#ifndef RASPI
    delete capture;
#endif
}

bool BetterVideoCapture::open(int device)
{
#ifndef RASPI

    return capture->open(device);
#else
    rpi_capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    rpi_capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    rpi_capture.set(CV_CAP_PROP_EXPOSURE, 3);
   // rpi_capture.set(CV_CAP_PROP_BRIGHTNESS, 30);
    return rpi_capture.open();
#endif
}

double BetterVideoCapture::getProperty(int propIdx)
{
#ifndef RASPI
    return capture->get(propIdx);
#else
    return rpi_capture.get(propIdx);
#endif
}

bool BetterVideoCapture::setProperty(int propIdx,double propVal)
{
#ifndef RASPI
    return capture->set(propIdx,propVal);
#else
    //rpi_capture.set( CV_CAP_PROP_FORMAT, CV_8UC3 );
   // return rpi_capture.set(propIdx, propVal);
    return true;
#endif
}

bool BetterVideoCapture::grabFrame()
{
#ifndef RASPI
    return capture->grab();
#else
    return rpi_capture.grab();
#endif
}

cv::Mat BetterVideoCapture::retrieveFrame()
{
#ifndef RASPI
    capture->retrieve(rawImage);
    return rawImage(cv::Rect(80, 0, 480, 480));
#else
    rpi_capture.retrieve(rawImage);
    cv::flip(rawImage.t(), rawImage, 1);
    return rawImage(cv::Rect(0, 80, 480, 480));
#endif
    // qDebug() << "RawImage retrieved: " << type2str(rawImage);

}

bool BetterVideoCapture::isOpened() const
{
#ifndef RASPI
    return capture->isOpened();
#else
    return rpi_capture.isOpened();
#endif
}

QString BetterVideoCapture::type2str(cv::Mat& mat) {
  int type = mat.type();
  QString r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');
  return r;
}

