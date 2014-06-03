#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QTimer>
#include <QStringList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtSerialPort/QSerialPortInfo>

bool running = false;
bool stepperEnabled = false;
bool extHeatEnabled = false;
bool bedHeatEnabled = false;
bool waitOnTemps = false;
bool fileListMode = false;
bool sdcardOpened = false;
bool multipleTemps = false;
bool commConnected = false;

QString m_qsettingsFilename = "default.ini";

QStringList m_serialports;

int lastExtheatset = 0;
int lastBedheatset = 0;
double currexttemp = 0;
double currbedtemp = 0;

int timerticks = 0;
int Lgraphscale = 1;
int Lgraphoffset = 0;
int Rgraphscale = 1;
int Rgraphoffset = 0;
int graphlength = 0;
int graphheadpos = 0;
int graphhistarray[151][4] ;
QPen penarray[4] = {QPen(QBrush(QColor(90, 170, 100, 255), Qt::SolidPattern), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin),
                    QPen(QBrush(QColor(90, 170, 100, 255), Qt::SolidPattern), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin),
                    QPen(QBrush(QColor(80, 170, 255, 255), Qt::SolidPattern), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin),
                    QPen(QBrush(QColor(80, 170, 255, 255), Qt::SolidPattern), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin)};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // serialport
    m_serial = new QSerialPort(this);

    connect(ui->eStop, SIGNAL(clicked()), this, SLOT(eStop_clicked()));//
    connect(ui->eStepPwr, SIGNAL(clicked()), this, SLOT(eStepPwr_clicked()));//
  //  connect(ui->spinBoxExtTarget, SIGNAL(valueChanged (int)), this, SLOT(extSpinbox_changed()));
    connect(ui->ExtUpX10, SIGNAL(clicked()), this, SLOT(extTarget_Up_10()));//
    connect(ui->ExtUpX1, SIGNAL(clicked()), this, SLOT(extTarget_Up_1()));//
    connect(ui->ExtDnX1, SIGNAL(clicked()), this, SLOT(extTarget_Dn_1()));//
    connect(ui->ExtDnX10, SIGNAL(clicked()), this, SLOT(extTarget_Dn_10()));//

    connect(ui->extEnable, SIGNAL(clicked()), this, SLOT(extEnable_clicked()));
//    connect(ui->spinBoxBedTarget, SIGNAL(valueChanged (int)), this, SLOT(bedSpinbox_changed()));
    connect(ui->BedUpX10, SIGNAL(clicked()), this, SLOT(bedTarget_Up_10()));//
    connect(ui->BedUpX1, SIGNAL(clicked()), this, SLOT(bedTarget_Up_1()));//
    connect(ui->BedDnX1, SIGNAL(clicked()), this, SLOT(bedTarget_Dn_1()));//
    connect(ui->BedDnX10, SIGNAL(clicked()), this, SLOT(bedTarget_Dn_10()));//

    connect(ui->bedEnable, SIGNAL(clicked()), this, SLOT(bedEnable_clicked()));
    connect(ui->getCode, SIGNAL(clicked()), this, SLOT(getCode_clicked()));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(exitButton_clicked()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchButton_clicked()));
    connect(ui->comboBoxDevices, SIGNAL(activated(int)), this, SLOT(comboBoxDevices_clicked()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectButton_clicked()));//
    connect(ui->comboBoxFiles, SIGNAL(activated(int)), this, SLOT(comboBoxFiles_clicked()));
    connect(ui->waittempsButton, SIGNAL(clicked()), this, SLOT(waittempsButton_clicked()));

    m_chartScene.setSceneRect(0, 0, 600, 280);
    m_chartScene.setBackgroundBrush(Qt::white);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(periodic_update()));

    ui->comboBoxDevices->addItem("Select a Device to connect to","");
    ui->comboBoxFiles->addItem("No \"g\" code file selected","");
    ui->eStop->setStyleSheet("background-color: #00C000; border-radius: 5px; color : #ffffff;");

    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::eStop_clicked()
{
    if(commConnected)
    {
        if(running)
        {
            QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
            m_settings.beginGroup("Tx.Translate");
            QString data = m_settings.value("pauseprint", "No Translate").toString();
            ui->textBox->appendPlainText(data);
            data = data +  "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray

//            data = m_settings.value("disablesteppers", "No Translate").toString();
//            ui->textBox->appendPlainText(data);
//            data = data +  "\n";
//            MainWindow::writeData(data.toLatin1());  // const QByteArray
            m_settings.endGroup();

            ui->eStop->setText("GO");
            ui->eStop->setStyleSheet("background-color: #00C000; border-radius: 5px; color : #ffffff;");
            ui->textBox->appendPlainText("Emergency Stop");
            running = false;
        }
        else
        {
            QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
            m_settings.beginGroup("Tx.Translate");
            QString data = m_settings.value("startprint", "No Translate").toString();
            ui->textBox->appendPlainText(data);
            data = data +  "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray

//            data = m_settings.value("enablesteppers", "No Translate").toString();
//            ui->textBox->appendPlainText(data);
//            data = data +  "\n";
//            MainWindow::writeData(data.toLatin1());  // const QByteArray
            m_settings.endGroup();

            ui->eStop->setText("Emergency\nStop");
            ui->eStop->setStyleSheet("background-color: #F00000; border-radius: 5px; color : #ffffff;");
            ui->textBox->appendPlainText("Plot Started");

            running = true;
        }
    }
    else
        ui->textBox->appendPlainText("Port not connected for Start/Stop!");
}

void MainWindow::eStepPwr_clicked()
{
    if(commConnected)
    {
        if(stepperEnabled)
        {
            QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
            m_settings.beginGroup("Tx.Translate");
            QString data = m_settings.value("disablesteppers", "No Translate").toString();
            ui->textBox->appendPlainText(data);
            data = data +  "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray
            m_settings.endGroup();

            ui->eStepPwr->setText("Enable \nSteppers");
            ui->textBox->appendPlainText("Steppers Manually Disabled");
            stepperEnabled = false;
        }
        else
        {
            QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
            m_settings.beginGroup("Tx.Translate");
            QString data = m_settings.value("enablesteppers", "No Translate").toString();
            ui->textBox->appendPlainText(data);
            data = data +  "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray
            m_settings.endGroup();

            ui->eStepPwr->setText("Disable\nSteppers");
           ui->textBox->appendPlainText("Steppers Manually Enabled");

            stepperEnabled = true;
        }
    }
    else
        ui->textBox->appendPlainText("Port not connected for Steppers commands!");
}

void  MainWindow::extTarget_Up_10()
{
  int temptemp = ui->lblExtTarget->text().toInt();
    if( temptemp < 250 )
    {
        temptemp += 10;
        ui->lblExtTarget->setNum(temptemp);
        ui->extEnable->setText("Set Ext temp");
        extHeatEnabled = false;
    }
}

void  MainWindow::extTarget_Up_1()
{
  int temptemp = ui->lblExtTarget->text().toInt();
    if( temptemp < 260 )
    {
        temptemp += 1;
        ui->lblExtTarget->setNum(temptemp);
      ui->extEnable->setText("Set Ext temp");
      extHeatEnabled = false;
    }
}

void  MainWindow::extTarget_Dn_1()
{
  int temptemp = ui->lblExtTarget->text().toInt();
    if( temptemp > 20 )
    {
        temptemp -= 1;
        ui->lblExtTarget->setNum(temptemp);
      ui->extEnable->setText("Set Ext temp");
      extHeatEnabled = false;
    }
}

void  MainWindow::extTarget_Dn_10()
{
  int temptemp = ui->lblExtTarget->text().toInt();
    if( temptemp > 30 )
    {
        temptemp -= 10;
        ui->lblExtTarget->setNum(temptemp);
        ui->extEnable->setText("Set Ext temp");
        extHeatEnabled = false;
    }
}

void MainWindow::extEnable_clicked()
{
  QString data;

//    ui->textBox->appendPlainText(tr("Update Extruder Setpoint clicked"));

    if( commConnected == false )
        ui->textBox->appendPlainText(tr("Port not connected for Ext Temp Set!"));
    else
    {
        QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
        m_settings.beginGroup("Tx.Translate");

        if( extHeatEnabled == false )
        {
            lastExtheatset =  ui->lblExtTarget->text().toInt();

            data = m_settings.value("setexttemp", "").toString() % QString(" ") %
                   m_settings.value("setcommand", "").toString() % QString::number(lastExtheatset);
            ui->textBox->appendPlainText(data);
            data = data + "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray

            ui->extEnable->setText("Stop Ext heat");
            extHeatEnabled = true;
        }
        else
        {
            data = m_settings.value("setexttemp", "").toString() % QString(" ") %
                   m_settings.value("heatdisable", "").toString();
            ui->textBox->appendPlainText(data);
            data = data + "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray

            ui->extEnable->setText("Start Ext heat");
            extHeatEnabled = false;
        }
        m_settings.endGroup();
    }
}

void  MainWindow::bedTarget_Up_10()
{
  int temptemp = ui->lblBedTarget->text().toInt();
    if( temptemp < 250 )
    {
        temptemp += 10;
        ui->lblBedTarget->setNum(temptemp);
        ui->bedEnable->setText("Set Bed temp");
        bedHeatEnabled = false;
    }
}

void  MainWindow::bedTarget_Up_1()
{
  int temptemp = ui->lblBedTarget->text().toInt();
    if( temptemp < 260 )
    {
        temptemp += 1;
        ui->lblBedTarget->setNum(temptemp);
        ui->bedEnable->setText("Set Bed temp");
        bedHeatEnabled = false;
    }
}

void  MainWindow::bedTarget_Dn_1()
{
  int temptemp = ui->lblBedTarget->text().toInt();
    if( temptemp > 20 )
    {
        temptemp -= 1;
        ui->lblBedTarget->setNum(temptemp);
        ui->bedEnable->setText("Set Bed temp");
        bedHeatEnabled = false;
    }
}

void  MainWindow::bedTarget_Dn_10()
{
  int temptemp = ui->lblBedTarget->text().toInt();
    if( temptemp > 30 )
    {
        temptemp -= 10;
        ui->lblBedTarget->setNum(temptemp);
        ui->bedEnable->setText("Set Bed temp");
        bedHeatEnabled = false;
    }
}

void MainWindow::bedEnable_clicked()
{
  QString data;

//    ui->textBox->appendPlainText(tr("Update Bed Setpoint clicked"));

    if( commConnected == false )
        ui->textBox->appendPlainText(tr("Port not connected for Bed Temp Set!"));
    else
    {
        QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
        m_settings.beginGroup("Tx.Translate");

        if( bedHeatEnabled == false )
        {
            lastBedheatset =  ui->lblBedTarget->text().toInt();

            data = m_settings.value("setbedtemp", "").toString() % QString(" ") %
                   m_settings.value("setcommand", "").toString() % QString::number(lastBedheatset);
            ui->textBox->appendPlainText(data);
            data = data + "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray

            ui->bedEnable->setText("Stop Bed heat");
            bedHeatEnabled = true;
        }
        else
        {
            data = m_settings.value("setbedtemp", "").toString() % QString(" ") %
                   m_settings.value("heatdisable", "").toString();
            ui->textBox->appendPlainText(data);
            data = data + "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray

            ui->bedEnable->setText("Start Bed heat");
            bedHeatEnabled = false;
        }
        m_settings.endGroup();
    }
}

void MainWindow::getCode_clicked()
{
  QString data ;

    if( commConnected == false )
        ui->textBox->appendPlainText(tr("Port not connected for getCode!"));
    else
    {
        ui->comboBoxFiles->clear();
        QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
        m_settings.beginGroup("Tx.Translate");
        if( sdcardOpened == false )
        {
            data = m_settings.value("initsdcard", "No Translate").toString();
            ui->textBox->appendPlainText(data);
            data = data +  "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray
            sdcardOpened = true;
        }

        data = m_settings.value("listsdcard", "No Translate").toString();
        ui->textBox->appendPlainText(data);
        data = data +  "\n";
        MainWindow::writeData(data.toLatin1());  // const QByteArray

        m_settings.endGroup();
    }
}

void MainWindow::exitButton_clicked()
{
    close();
}

void MainWindow::searchButton_clicked()
{
  QString port;
  //static const QString blankString = QObject::tr("N/A");

    ui->comboBoxDevices->clear();
    m_serialports.QList::clear();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        port = QObject::tr("Port: ") + info.portName() + QObject::tr(" - ") + info.description() + "\n";
        ui->comboBoxDevices->addItem(port);

        m_serialports << (info.systemLocation());
    }
}

void MainWindow::comboBoxDevices_clicked()
{

//    ui->textBox->appendPlainText(m_serialports.at(ui->comboBoxDevices->currentIndex()));
    QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
    m_settings.beginGroup("Port.Specs");
    m_settings.setValue("name",m_serialports.at(ui->comboBoxDevices->currentIndex()));
    m_settings.endGroup();
}

void MainWindow::connectButton_clicked()
{
        if(commConnected)
       {
//            Don't think this disable SD card is desireable. 
//            if( sdcardOpened == true )
//            {
//                QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
//                m_settings.beginGroup("Tx.Translate");
//                QString data = m_settings.value("relsdcard", "No Translate").toString();
//                ui->textBox->appendPlainText(data);
//                data = data +  "\n";
//                MainWindow::writeData(data.toLatin1());  // const QByteArray
//                m_settings.endGroup();
//                sdcardOpened = false;
//            }

            MainWindow::closeSerialPort();
            ui->connectButton->setText("Connect");
            commConnected = false;
            // Clean up application internal state.
            ui->extEnable->setText("Start Ext heat");
            ui->bedEnable->setText("Start Bed heat");
            extHeatEnabled = false;
            bedHeatEnabled = false;
            waitOnTemps = false;
            sdcardOpened = false;
        }
        else
        {
            if ( true == MainWindow::openSerialPort() )
            {
                MainWindow::connectSerialPort();
                // Synchronous read with no error on longer, blocking timeout to wait for the printer..
                QString data;
                while (m_serial->waitForReadyRead(1000))
                     data.append(m_serial->readAll());
                ui->textBox->appendPlainText(data);

                for(int period = 0; period < 150; period++)
                    for(int indx = 0; indx < 4; indx++)
                        graphhistarray[period][indx] = 0;

                ui->connectButton->setText("Disconnect");
                commConnected = true;
            }
        }

}

void MainWindow::comboBoxFiles_clicked()
{

    ui->textBox->appendPlainText(tr("comboBoxFiles_clicked"));
    if(commConnected)
    {
        if( sdcardOpened == true )
        {
            QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
            m_settings.beginGroup("Tx.Translate");
            QString data = m_settings.value("selectfile", "No Translate").toString() %
                           QString(" ") % ui->comboBoxFiles->currentText().toLower();
            ui->textBox->appendPlainText(data);
            data = data +  "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray
            m_settings.endGroup();
        }
        else
            ui->textBox->appendPlainText("Go get the \"G\" file list!");
    }
    else
        ui->textBox->appendPlainText("Port not connected for \"G\" code Files!");
}

void MainWindow::waittempsButton_clicked()
{
    if(commConnected)
    {
        if(waitOnTemps)
        {
            QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
            m_settings.beginGroup("Tx.Translate");
            QString data = m_settings.value("waitcontrol", "No Translate").toString() % QString(" ") %
                           m_settings.value("waitdisable", "No Translate").toString();
            ui->textBox->appendPlainText(data);
            data = data +  "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray
            m_settings.endGroup();

            ui->waittempsButton->setText("Wait for Temps");
            waitOnTemps = false;
        }
        else
        {
            QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
            m_settings.beginGroup("Tx.Translate");
            QString data = m_settings.value("waitcontrol", "No Translate").toString() % QString(" ") %
                    m_settings.value("waitenable", "No Translate").toString();
            ui->textBox->appendPlainText(data);
            data = data +  "\n";
            MainWindow::writeData(data.toLatin1());  // const QByteArray
            m_settings.endGroup();

            ui->waittempsButton->setText("No Wait for Temps");
            waitOnTemps = true;
        }
    }
    else
        ui->textBox->appendPlainText("Port not connected for No/Wait on Temps!");
}

void MainWindow::periodic_update()
{

    if(commConnected)
    {
        timerticks += 1;
        multipleTemps = false;
//        ui->textBox->appendPlainText(QObject::tr("TimeTick ") + QString::number(timerticks));

        QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
        m_settings.beginGroup("Tx.Translate");
        QString data = m_settings.value("gettemps", "No Translate").toString();
//        ui->textBox->appendPlainText(data);
        data = data +  "\n";
        MainWindow::writeData(data.toLatin1());  // const QByteArray
        m_settings.endGroup();
    }
}

void MainWindow::connectSerialPort()
{
    connect(m_serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

    connect(m_serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

bool MainWindow::openSerialPort()
{

    // Get the port parameters from default.ini here
    QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
    m_settings.beginGroup("Port.Specs");

    m_serial->reset();
    m_serial->setPortName(m_settings.value("name", "").toString()); // Was p.name
    if (m_serial->open(QIODevice::ReadWrite))
    {
        if (m_serial->setBaudRate(m_settings.value("baud", "-1").toInt(), (QSerialPort::Directions)3) // Was p.baudRate
            && m_serial->setDataBits((QSerialPort::DataBits)m_settings.value("data", "-1").toInt())
            && m_serial->setParity((QSerialPort::Parity)m_settings.value("parity", "-1").toInt())
            && m_serial->setStopBits((QSerialPort::StopBits)m_settings.value("stop", "-1").toInt())
            && m_serial->setFlowControl((QSerialPort::FlowControl)m_settings.value("flowctrl", "-1").toInt()))
//  Depreciated in 5.2.1          && m_serial->setDataErrorPolicy((QSerialPort::DataErrorPolicy)m_settings.value("datapolicy", "-1").toInt()))
        {
            while (!m_serial->atEnd())
                QByteArray data = m_serial->readAll();

            ui->textBox->appendPlainText(tr("Comm Port Connected"));
            ui->textBox->appendPlainText(tr("Baudrate = ") + QString::number((int)m_serial->baudRate()));
            ui->textBox->appendPlainText(tr("Data Bits = ") + QString::number((int)m_serial->dataBits()));
            ui->textBox->appendPlainText(tr("Parity = ") + QString::number((int)m_serial->parity()));
            ui->textBox->appendPlainText(tr("Port Name = ") + m_serial->portName());
        }
        else
        {
            m_serial->close();
            ui->textBox->appendPlainText(tr("Port config error - ") + m_serial->errorString());
            return(false);
        }
    }
    else
    {
        ui->textBox->appendPlainText(tr("Port open error - ") + m_serial->errorString());
        return(false);
    }

    return(true);
}

void MainWindow::closeSerialPort()
{
    m_serial->close();
}

void MainWindow::writeData(const QByteArray &data)
{
    m_serial->write(data);
}

// readData contains the QString parser of all data from the 3d printer. All decisions are here.
void MainWindow::readData()
{
  QString outstr;
  QRegExp numpat;
  QStringList values;

    QByteArray data = m_serial->readAll();
    while (m_serial->waitForReadyRead(100)) // Synchronous read with no error on short timeout.
        data.append(m_serial->readAll());

    QSettings m_settings(m_qsettingsFilename,QSettings::IniFormat);
    QRegExp delpat(m_settings.value("delimiterregexp", "").toString());

//    data = data.simplified(); Can't do because it removes linefeeds.
    QString instr(data);
//    instr.remove(QRegExp("[ ]")); Turns out I care about spaces.

    ui->textBox->appendPlainText("Raw data = " + instr.simplified());

    QStringList tokens = instr.split(delpat);

    m_settings.beginGroup("Rx.Translate");
    for ( int indx = 0; indx < tokens.size(); indx++ )
    {
//        ui->textBox->appendPlainText("Token string is " + tokens.at(indx) + "EndChar");
//        ui->textBox->appendPlainText("Token is " + m_settings.value(tokens.at(indx), 0).toString());

        switch(m_settings.value(tokens.at(indx), 0).toInt())
        {
        case 1:
            break;

        case 2:
            m_settings.endGroup();

            numpat = static_cast<QRegExp>(m_settings.value("numberregexp", "").toString());

            values = tokens.at(m_settings.value("exttempterm", 0).toInt() + indx).split(numpat);
//            ui->textBox->appendPlainText("Ext substring" + values.join("^"));
            currexttemp = values.at(m_settings.value("exttempoff", 0).toInt()).toDouble();
//            ui->textBox->appendPlainText("Ext Temp is " + QString::number(currexttemp);
            if( m_settings.value("enableset", 0).toInt() != 0 )
            {
                lastExtheatset = static_cast<int>(0.5 + values.at(m_settings.value("extsetoff", 0).toInt()).toDouble());
//                ui->textBox->appendPlainText("Ext set is " + QString::number(lastExtheatset));
            }
            values = tokens.at(m_settings.value("bedtempterm", 0).toInt() + indx).split(numpat);
//            ui->textBox->appendPlainText("Bed substring" + values.join("^"));
            currbedtemp = values.at(m_settings.value("bedtempoff", 0).toInt()).toDouble();
//            ui->textBox->appendPlainText("Bed Temp is " + QString::number(currbedtemp));
            if( m_settings.value("enableset", 0).toInt() != 0 )
            {
                lastBedheatset = static_cast<int>(0.5 + values.at(m_settings.value("bedsetoff", 0).toInt()).toDouble());
//                ui->textBox->appendPlainText("Bed set is " + QString::number(lastBedheatset));
            }
            MainWindow::charttemps(currexttemp, lastExtheatset, currbedtemp, lastBedheatset);

            if( m_settings.value("enableset", 0).toInt() != 0 )
                indx = indx + m_settings.value("bedtempterm", 0).toInt() + m_settings.value("bedsetoff", 0).toInt();
            else
                indx = indx + m_settings.value("bedtempterm", 0).toInt() + m_settings.value("bedtempoff", 0).toInt();

            m_settings.beginGroup("Rx.Translate");
            break;

        case 4:
            fileListMode = true;
            break;

        case 5:
            fileListMode = false;
            break;

        case 6:
            ui->eStop->setText("GO");
            ui->eStop->setStyleSheet("background-color: #00C000; border-radius: 5px; color : #ffffff;");
            ui->textBox->appendPlainText("Print Complete");
            running = false;
            break;

        case 7:
            m_settings.endGroup();

            numpat = static_cast<QRegExp>(m_settings.value("numberregexp", "").toString());

            values = tokens.at(m_settings.value("exttempterm", 0).toInt() + indx).split(numpat);
//            ui->textBox->appendPlainText("Ext substring" + values.join("^"));
            currexttemp = values.at(m_settings.value("exttempoff", 0).toInt()).toDouble();
//            ui->textBox->appendPlainText("Ext Temp is " + QString::number(currexttemp));
//   The E: data from the wait message is not good.
//            values = tokens.at(m_settings.value("bedtempterm", 0).toInt() + indx).split(numpat);
//            ui->textBox->appendPlainText("Set substring" + values.join("^"));
//            lastExtheatset = static_cast<int>(0.5 + values.at(m_settings.value("extwaitoff", 0).toInt()).toDouble());
//            ui->textBox->appendPlainText("Ext set is " + QString::number(lastExtheatset));

            MainWindow::charttemps(currexttemp, lastExtheatset, currbedtemp, lastBedheatset);

            indx = indx + m_settings.value("bedtempterm", 0).toInt() + m_settings.value("extwaitend", 0).toInt();
            m_settings.beginGroup("Rx.Translate");
            break;

        default:
            if( fileListMode == true )
                if(tokens.at(indx).simplified() != " " )
                    ui->comboBoxFiles->addItem(tokens.at(indx).simplified());
            break;
        }
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        ui->textBox->appendPlainText(tr("Critical Serial Port Error ") + m_serial->errorString());
        MainWindow::closeSerialPort();
    }
    else
        if( (int)error != 12 )  // Not Resource Temporarily Unavailable
            ui->textBox->appendPlainText(tr("Serial Port Error ") + QString::number((int)error) + " " + m_serial->errorString());
}

void MainWindow::charttemps(double temp1, int temp2, double temp3, int temp4 )
{
  int element, period, periodindex, lastindex, headvalue, tailvalue;
  int LlowWaterMark, LhighWaterMark, RlowWaterMark, RhighWaterMark, scale, offset;

    if(  multipleTemps == false )
    {
        ui->lblExtCurrent->setNum(temp1);
        ui->lblBedCurrent->setNum(temp3);

        m_chartScene.clear();

        //Put raw temp data into the history array here.
        graphhistarray[graphheadpos][0] = static_cast<int>(temp1 + .5);
        graphhistarray[graphheadpos][1] = temp2;
        graphhistarray[graphheadpos][2] = static_cast<int>(temp3 + .5);
        graphhistarray[graphheadpos][3] = temp4;

        //ReInitialize the high and low water marks here
        LlowWaterMark = 279;
        LhighWaterMark = 0;
        RlowWaterMark = 279;
        RhighWaterMark = 0;

        for(period = 0; period < graphlength; period++)
        {
            if( period <= graphheadpos)
                periodindex = graphheadpos - period;
            else
                periodindex = 151 + graphheadpos - period;

            if( periodindex == 0 )
                lastindex = 150;
            else
                lastindex = periodindex - 1;

            for(element = 0; element < 4; element++)
            {
                //AutoRange limits check here
                tailvalue = graphhistarray[lastindex][element];
                headvalue = graphhistarray[periodindex][element];

                if( element < 2 )
                {
                    if( LlowWaterMark > tailvalue )
                        LlowWaterMark = tailvalue;
                    if( LlowWaterMark > headvalue )
                        LlowWaterMark = headvalue;
                    if( LhighWaterMark < tailvalue )
                        LhighWaterMark = tailvalue;
                    if( LhighWaterMark < headvalue )
                        LhighWaterMark = headvalue;
                }
                else
                {
                    if( RlowWaterMark > tailvalue )
                        RlowWaterMark = tailvalue;
                    if( RlowWaterMark > headvalue )
                        RlowWaterMark = headvalue;
                    if( RhighWaterMark < tailvalue )
                        RhighWaterMark = tailvalue;
                    if( RhighWaterMark < headvalue )
                        RhighWaterMark = headvalue;
                }


                //AutoRange value scaling here
                if( element < 2 )
                {
                    tailvalue = ((tailvalue - Lgraphoffset) * Lgraphscale) + 140;
                    headvalue = ((headvalue - Lgraphoffset) * Lgraphscale) + 140;
                }
                else
                {
                    tailvalue = ((tailvalue - Rgraphoffset) * Rgraphscale) + 140;
                    headvalue = ((headvalue - Rgraphoffset) * Rgraphscale) + 140;
                }
                if( tailvalue > 279 )
                    tailvalue = 279;
                if( tailvalue < 0 )
                    tailvalue = 0;
                if( headvalue > 279 )
                    headvalue = 279;
                if( headvalue < 0 )
                    headvalue = 0;

                if( (element == 0) || (element == 2) || ((period & 1) == 1) || (headvalue != tailvalue) ) //Make target temps dotted lines.
                m_chartScene.addLine(595 - (period * 4), 279 - tailvalue,
                                     599 - (period * 4), 279 - headvalue, penarray[element]);
            }
        }

        //AutoRange scaling range adjust here
        Lgraphoffset = ((LhighWaterMark + LlowWaterMark + 10) / 20) * 10; //Average value modulo 20 always positive.
        Rgraphoffset = (((RhighWaterMark + RlowWaterMark + 10) / 20) * 10) + 5; //Average value modulo 20 always positive.

        for(scale = 1; scale < 7; scale++) // Autorange is x1 - x6
        {
            if( (((LhighWaterMark - Lgraphoffset ) * scale) < 140) && (((Lgraphoffset - LlowWaterMark) * scale) < 140) )
            {
                Lgraphscale = scale;
            }
            if( (((RhighWaterMark - Rgraphoffset ) * scale) < 140) && (((Rgraphoffset - RlowWaterMark) * scale) < 140) )
            {
                Rgraphscale = scale;
            }
        }

        //Update the labels here. Adjust the offset to keep the labels in range.
        //No longer adjust the offset up to make sure the low label is positive.
        //        do  //Keep the low label above 10
        //        {
        //            if( scale > 10 )
        //                break;
        //            graphoffset += 10;
        //        } while(graphoffset < 160);
        //No longer report autorange data.
        //  ui->textBox->appendPlainText(tr("Scale is ") + QString::number((int)graphscale) + tr(" Offset is ") + QString::number((int)graphoffset));
        //  ui->textBox->appendPlainText(tr("Low is ") + QString::number((int)scale) + tr(" High is ") + QString::number((int)offset));
        //  offset = (temp2 * graphscale) - graphscale;
        //  ui->textBox->appendPlainText(tr("Target position is ") + QString::number((int)offset));

        scale = Lgraphoffset - (120 / Lgraphscale);
        ui->label_0_l->setNum(scale);
        ui->label_0_m->setNum(Lgraphoffset);
        offset = Lgraphoffset + (120 / Lgraphscale);
        ui->label_0_h->setNum(offset);

        scale = Rgraphoffset - (120 / Rgraphscale);
        ui->label_4_l->setNum(scale);
        ui->label_4_m->setNum(Rgraphoffset);
        offset = Rgraphoffset + (120 / Rgraphscale);
        ui->label_4_h->setNum(offset);

        //Update the graphics scene.
        ui->graphicsView->setScene( &m_chartScene );
        ui->graphicsView->show();

        //Increment the FIFO array pointers
        graphheadpos += 1;
        if( graphheadpos == 151 )
            graphheadpos = 0;
        if( graphlength < 150 )
            graphlength += 1;

         multipleTemps = true;
    }
}


