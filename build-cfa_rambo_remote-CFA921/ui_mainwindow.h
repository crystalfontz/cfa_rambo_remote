/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Oct 24 11:08:38 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *frameExtruder;
    QSpinBox *spinBoxExtTarget;
    QLabel *lblExtCurrent;
    QLabel *label_1;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *extEnable;
    QGraphicsView *graphicsView;
    QFrame *frameExtruder_2;
    QSpinBox *spinBoxBedTarget;
    QLabel *lblBedCurrent;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *bedEnable;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QFrame *frame;
    QPushButton *GCode;
    QPushButton *eStop;
    QLabel *lblGCodeStatus;
    QComboBox *comboBoxDevices;
    QLabel *label_2;
    QLabel *lblConnectionStatus;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        MainWindow->setMaximumSize(QSize(800, 480));
        QFont font;
        font.setFamily(QString::fromUtf8("FreeSans"));
        font.setPointSize(11);
        font.setItalic(false);
        MainWindow->setFont(font);
        MainWindow->setAutoFillBackground(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frameExtruder = new QFrame(centralWidget);
        frameExtruder->setObjectName(QString::fromUtf8("frameExtruder"));
        frameExtruder->setGeometry(QRect(10, 50, 110, 160));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(85, 170, 127, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        frameExtruder->setPalette(palette);
        frameExtruder->setAutoFillBackground(true);
        frameExtruder->setFrameShape(QFrame::NoFrame);
        frameExtruder->setLineWidth(1);
        frameExtruder->setMidLineWidth(0);
        spinBoxExtTarget = new QSpinBox(frameExtruder);
        spinBoxExtTarget->setObjectName(QString::fromUtf8("spinBoxExtTarget"));
        spinBoxExtTarget->setGeometry(QRect(10, 40, 90, 22));
        lblExtCurrent = new QLabel(frameExtruder);
        lblExtCurrent->setObjectName(QString::fromUtf8("lblExtCurrent"));
        lblExtCurrent->setGeometry(QRect(10, 90, 90, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush2(QColor(233, 231, 227, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        lblExtCurrent->setPalette(palette1);
        lblExtCurrent->setAutoFillBackground(true);
        lblExtCurrent->setFrameShape(QFrame::Panel);
        lblExtCurrent->setFrameShadow(QFrame::Sunken);
        label_1 = new QLabel(frameExtruder);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setGeometry(QRect(0, 0, 110, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush3(QColor(110, 109, 106, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_1->setPalette(palette2);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Abyssinica SIL"));
        font1.setPointSize(14);
        label_1->setFont(font1);
        label_1->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frameExtruder);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 90, 21));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_5->setPalette(palette3);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Abyssinica SIL"));
        font2.setPointSize(12);
        label_5->setFont(font2);
        label_6 = new QLabel(frameExtruder);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 70, 90, 21));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_6->setPalette(palette4);
        label_6->setFont(font2);
        extEnable = new QPushButton(frameExtruder);
        extEnable->setObjectName(QString::fromUtf8("extEnable"));
        extEnable->setGeometry(QRect(10, 120, 90, 27));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(150, 50, 610, 290));
        graphicsView->setFrameShape(QFrame::Panel);
        graphicsView->setFrameShadow(QFrame::Raised);
        frameExtruder_2 = new QFrame(centralWidget);
        frameExtruder_2->setObjectName(QString::fromUtf8("frameExtruder_2"));
        frameExtruder_2->setGeometry(QRect(10, 210, 110, 160));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush4(QColor(85, 170, 255, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        frameExtruder_2->setPalette(palette5);
        frameExtruder_2->setAutoFillBackground(true);
        frameExtruder_2->setFrameShape(QFrame::NoFrame);
        frameExtruder_2->setLineWidth(1);
        frameExtruder_2->setMidLineWidth(0);
        spinBoxBedTarget = new QSpinBox(frameExtruder_2);
        spinBoxBedTarget->setObjectName(QString::fromUtf8("spinBoxBedTarget"));
        spinBoxBedTarget->setGeometry(QRect(10, 40, 90, 22));
        lblBedCurrent = new QLabel(frameExtruder_2);
        lblBedCurrent->setObjectName(QString::fromUtf8("lblBedCurrent"));
        lblBedCurrent->setGeometry(QRect(10, 90, 90, 21));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        lblBedCurrent->setPalette(palette6);
        lblBedCurrent->setAutoFillBackground(true);
        lblBedCurrent->setFrameShape(QFrame::Panel);
        lblBedCurrent->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frameExtruder_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(0, 0, 110, 21));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Active, QPalette::Base, brush);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        label_7->setPalette(palette7);
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(frameExtruder_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 70, 90, 21));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_8->setPalette(palette8);
        label_8->setFont(font2);
        label_9 = new QLabel(frameExtruder_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 20, 90, 21));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_9->setPalette(palette9);
        label_9->setFont(font2);
        bedEnable = new QPushButton(frameExtruder_2);
        bedEnable->setObjectName(QString::fromUtf8("bedEnable"));
        bedEnable->setGeometry(QRect(10, 120, 90, 27));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 50, 30, 290));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::Base, brush);
        palette10.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette10.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette10.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette10.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label->setPalette(palette10);
        label->setAutoFillBackground(true);
        label->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 340, 670, 30));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::Base, brush);
        palette11.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette11.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette11.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette11.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        label_3->setPalette(palette11);
        label_3->setAutoFillBackground(true);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(760, 50, 30, 290));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::Base, brush);
        palette12.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette12.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette12.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette12.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        label_4->setPalette(palette12);
        label_4->setAutoFillBackground(true);
        label_4->setAlignment(Qt::AlignCenter);
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 380, 781, 90));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Plain);
        GCode = new QPushButton(frame);
        GCode->setObjectName(QString::fromUtf8("GCode"));
        GCode->setGeometry(QRect(10, 10, 70, 70));
        eStop = new QPushButton(frame);
        eStop->setObjectName(QString::fromUtf8("eStop"));
        eStop->setGeometry(QRect(700, 10, 70, 70));
        lblGCodeStatus = new QLabel(frame);
        lblGCodeStatus->setObjectName(QString::fromUtf8("lblGCodeStatus"));
        lblGCodeStatus->setGeometry(QRect(90, 10, 601, 71));
        lblGCodeStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        comboBoxDevices = new QComboBox(centralWidget);
        comboBoxDevices->setObjectName(QString::fromUtf8("comboBoxDevices"));
        comboBoxDevices->setGeometry(QRect(90, 20, 270, 26));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 20, 70, 21));
        label_2->setFont(font1);
        lblConnectionStatus = new QLabel(centralWidget);
        lblConnectionStatus->setObjectName(QString::fromUtf8("lblConnectionStatus"));
        lblConnectionStatus->setGeometry(QRect(370, 20, 110, 21));
        lblConnectionStatus->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CFA921 RAMbo Remote", 0, QApplication::UnicodeUTF8));
        lblExtCurrent->setText(QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("MainWindow", "Extruder", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Target", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        extEnable->setText(QApplication::translate("MainWindow", "Enable", 0, QApplication::UnicodeUTF8));
        lblBedCurrent->setText(QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Bed", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Target", 0, QApplication::UnicodeUTF8));
        bedEnable->setText(QApplication::translate("MainWindow", "Enable", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p>250</p><p><br/></p><p><br/></p><p><br/>200</p><p><br/><br/></p><p><br/></p><p><br/>150</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p>150</p><p><br/></p><p><br/></p><p><br/>100</p><p><br/><br/></p><p><br/></p><p><br/>50</p></body></html>", 0, QApplication::UnicodeUTF8));
        GCode->setText(QApplication::translate("MainWindow", "Select\n"
"GCODE\n"
"File", 0, QApplication::UnicodeUTF8));
        eStop->setText(QApplication::translate("MainWindow", "GO", 0, QApplication::UnicodeUTF8));
        lblGCodeStatus->setText(QApplication::translate("MainWindow", "No File Loaded", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Devices:", 0, QApplication::UnicodeUTF8));
        lblConnectionStatus->setText(QApplication::translate("MainWindow", "Not Connected", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
