#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.showFullScreen(); // Was show to include the status bar.
    
    return a.exec();
}
