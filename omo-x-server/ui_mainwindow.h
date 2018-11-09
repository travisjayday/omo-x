/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cvimagewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayoutLeft;
    CVImageWidget *mCVImageWidget;
    QVBoxLayout *verticalLayoutRight;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QTextEdit *textEdit_name;
    QPushButton *btn_trainFace;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_2;
    QPushButton *switchCamViews;
    QRadioButton *radio_btn_isRGB;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton;
    QLabel *label_3;
    QSlider *slider_resolution;
    QLabel *label_downsampleF;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_4;
    QPushButton *remote_shutdown_btn;
    QSpacerItem *verticalSpacer;
    QLabel *label_status;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 742);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayoutLeft = new QVBoxLayout();
        verticalLayoutLeft->setSpacing(6);
        verticalLayoutLeft->setObjectName(QStringLiteral("verticalLayoutLeft"));
        verticalLayoutLeft->setSizeConstraint(QLayout::SetDefaultConstraint);
        mCVImageWidget = new CVImageWidget(centralWidget);
        mCVImageWidget->setObjectName(QStringLiteral("mCVImageWidget"));
        mCVImageWidget->setStyleSheet(QStringLiteral("background:gray"));

        verticalLayoutLeft->addWidget(mCVImageWidget);

        verticalLayoutLeft->setStretch(0, 2);

        horizontalLayout->addLayout(verticalLayoutLeft);

        verticalLayoutRight = new QVBoxLayout();
        verticalLayoutRight->setSpacing(0);
        verticalLayoutRight->setObjectName(QStringLiteral("verticalLayoutRight"));
        verticalLayoutRight->setContentsMargins(-1, -1, -1, 0);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(16);
        font.setUnderline(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayoutRight->addWidget(label);

        verticalSpacer_3 = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayoutRight->addItem(verticalSpacer_3);

        textEdit_name = new QTextEdit(centralWidget);
        textEdit_name->setObjectName(QStringLiteral("textEdit_name"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit_name->sizePolicy().hasHeightForWidth());
        textEdit_name->setSizePolicy(sizePolicy1);
        textEdit_name->setMaximumSize(QSize(200, 40));

        verticalLayoutRight->addWidget(textEdit_name);

        btn_trainFace = new QPushButton(centralWidget);
        btn_trainFace->setObjectName(QStringLiteral("btn_trainFace"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_trainFace->sizePolicy().hasHeightForWidth());
        btn_trainFace->setSizePolicy(sizePolicy2);
        btn_trainFace->setMaximumSize(QSize(200, 200));

        verticalLayoutRight->addWidget(btn_trainFace);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayoutRight->addItem(verticalSpacer_2);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayoutRight->addWidget(label_2);

        switchCamViews = new QPushButton(centralWidget);
        switchCamViews->setObjectName(QStringLiteral("switchCamViews"));
        switchCamViews->setMaximumSize(QSize(200, 16777215));

        verticalLayoutRight->addWidget(switchCamViews);

        radio_btn_isRGB = new QRadioButton(centralWidget);
        radio_btn_isRGB->setObjectName(QStringLiteral("radio_btn_isRGB"));
        radio_btn_isRGB->setLayoutDirection(Qt::LeftToRight);
        radio_btn_isRGB->setStyleSheet(QStringLiteral("margin-left: 10px; margin-top: 5px"));

        verticalLayoutRight->addWidget(radio_btn_isRGB);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayoutRight->addItem(verticalSpacer_4);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayoutRight->addWidget(pushButton);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayoutRight->addWidget(label_3);

        slider_resolution = new QSlider(centralWidget);
        slider_resolution->setObjectName(QStringLiteral("slider_resolution"));
        slider_resolution->setValue(99);
        slider_resolution->setOrientation(Qt::Horizontal);

        verticalLayoutRight->addWidget(slider_resolution);

        label_downsampleF = new QLabel(centralWidget);
        label_downsampleF->setObjectName(QStringLiteral("label_downsampleF"));
        label_downsampleF->setStyleSheet(QStringLiteral("margin-left:10px"));
        label_downsampleF->setMargin(0);

        verticalLayoutRight->addWidget(label_downsampleF);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayoutRight->addItem(verticalSpacer_5);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayoutRight->addWidget(label_4);

        remote_shutdown_btn = new QPushButton(centralWidget);
        remote_shutdown_btn->setObjectName(QStringLiteral("remote_shutdown_btn"));

        verticalLayoutRight->addWidget(remote_shutdown_btn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutRight->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayoutRight);

        horizontalLayout->setStretch(0, 10);

        verticalLayout->addLayout(horizontalLayout);

        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QStringLiteral("label_status"));
        QFont font1;
        font1.setFamily(QStringLiteral("MS Sans Serif"));
        font1.setPointSize(22);
        label_status->setFont(font1);
        label_status->setStyleSheet(QStringLiteral("border: 5px solid gray; background-color: white"));
        label_status->setAlignment(Qt::AlignCenter);
        label_status->setMargin(10);

        verticalLayout->addWidget(label_status);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Add Face", Q_NULLPTR));
        btn_trainFace->setText(QApplication::translate("MainWindow", "TrainFace", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Camera", Q_NULLPTR));
        switchCamViews->setText(QApplication::translate("MainWindow", "Local", Q_NULLPTR));
        radio_btn_isRGB->setText(QApplication::translate("MainWindow", "Network Camera isRGB", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Resolution", Q_NULLPTR));
        label_downsampleF->setText(QApplication::translate("MainWindow", "Downsampling Factor: 1", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Remote", Q_NULLPTR));
        remote_shutdown_btn->setText(QApplication::translate("MainWindow", "Remote Shutdown", Q_NULLPTR));
        label_status->setText(QApplication::translate("MainWindow", "Hello", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
