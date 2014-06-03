#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QSettings>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QtSerialPort/QSerialPort>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void eStop_clicked();
    void eStepPwr_clicked();
//    void extSpinbox_changed();
    void  extTarget_Up_10();
    void  extTarget_Up_1();
    void  extTarget_Dn_1();
    void  extTarget_Dn_10();

    void extEnable_clicked();
//    void bedSpinbox_changed();
    void  bedTarget_Up_10();
    void  bedTarget_Up_1();
    void  bedTarget_Dn_1();
    void  bedTarget_Dn_10();

    void bedEnable_clicked();
    void getCode_clicked();
    void exitButton_clicked();
    void searchButton_clicked();
    void comboBoxDevices_clicked();
    void connectButton_clicked();
    void comboBoxFiles_clicked();
    void waittempsButton_clicked();
    void periodic_update();

    void handleError(QSerialPort::SerialPortError error);
    void readData();

private:
    Ui::MainWindow *ui;

    QSerialPort *m_serial;

    QGraphicsScene m_chartScene;
    void charttemps(double temp1, int temp2, double temp3, int temp4 );

    void connectSerialPort();
//    void handleError(QSerialPort::SerialPortError error);

    bool openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
};

#endif // MAINWINDOW_H
