#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T11:54:58
#
#-------------------------------------------------

QT       += core gui
CONFIG += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RamboRemote
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

isEmpty(CROSSCOMPILE) {
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-qtserialport-Desktop-Debug/lib -lQtSerialPort
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-qtserialport-Desktop-Debug/lib -lQtSerialPort
else:unix:CONFIG(release, debug|release): LIBS += -L../build-qtserialport-Desktop-Debug/lib -lQtSerialPort
else:unix:CONFIG(debug, debug|release): LIBS += -L../build-qtserialport-Desktop-Debug/lib -lQtSerialPort

win32:CONFIG(release, debug|release): INCLUDEPATH += $$PWD/../build-qtserialport-Desktop-Debug/include
else:win32:CONFIG(debug, debug|release): INCLUDEPATH += $$PWD/../build-qtserialport-Desktop-Debug/include
else:unix:CONFIG(release, debug|release): INCLUDEPATH += $$PWD/../qtserialport-opensource-src-5.2.1/include/
else:unix:CONFIG(debug, debug|release): INCLUDEPATH += $$PWD/../qtserialport-opensource-src-5.2.1/include
    } else {
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-qtserialport-Desktop-Debug/lib -lQtSerialPort
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-qtserialport-Desktop-Debug/lib  -lQtSerialPort
else:unix:CONFIG(release, debug|release): LIBS += -L/root/Downloads/CFA921-usr/lib -lQtSerialPort$${QT_LIBINFIX}
else:unix:CONFIG(debug, debug|release): LIBS += -L/root/Downloads/CFA921-usr/lib -lQtSerialPort$${QT_LIBINFIX}

win32:CONFIG(release, debug|release): INCLUDEPATH += $$PWD/../build-qtserialport-Desktop-Debug/include
else:win32:CONFIG(debug, debug|release): INCLUDEPATH += $$PWD/../build-qtserialport-Desktop-Debug/include
else:unix:CONFIG(release, debug|release): INCLUDEPATH += /root/Downloads/CFA921-usr/include
else:unix:CONFIG(debug, debug|release): INCLUDEPATH += /root/Downloads/CFA921-usr/include
}
