#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

bool running = false;
bool extEnabled = false;
bool bedEnabled = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->eStop, SIGNAL(clicked()), this, SLOT(eStop_clicked()));
    connect(ui->extEnable, SIGNAL(clicked()), this, SLOT(extEnable_clicked()));
    connect(ui->bedEnable, SIGNAL(clicked()), this, SLOT(bedEnable_clicked()));
    connect(ui->GCode, SIGNAL(clicked()), this, SLOT(GCode_clicked()));

    ui->comboBoxDevices->addItem("Select a device to connect to","");
    ui->comboBoxDevices->addItem("RAMbo Board","Rambo");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::eStop_clicked()
{
    if(running)
    {
        ui->eStop->setText("GO");
        running = false;
    }
    else
    {
        //palette *tempPalette;
        //tempPalette->
        ui->eStop->setText("Emergency\nStop");
        //ui->eStop->palette()
        running = true;
    }
}
void MainWindow::extEnable_clicked()
{
    if(extEnabled)
    {
        ui->extEnable->setText("Enable");
        extEnabled = false;
    }
    else
    {
        ui->extEnable->setText("Disable");
        extEnabled = true;
    }
}
void MainWindow::bedEnable_clicked()
{
    if(bedEnabled)
    {
        ui->bedEnable->setText("Enable");
        bedEnabled = false;
    }
    else
    {
        ui->bedEnable->setText("Disable");
        bedEnabled = true;
    }
}
void MainWindow::GCode_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("GCode Files (*.gcode);;All Files (*.*)"));
    if(fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            //QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        // find out how big the file is and use a progressDialog to display the reading of trhe data before stating "done reading. file loaded"
        //in >> "thing to hold code";
        ui->lblGCodeStatus->setText(tr("File: %1 loaded").arg(fileName));
    }
}

/*void TextFinder::loadTextFile()
{
    QFile inputFile(":/input.txt");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->textEdit->setPlainText(line);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}*/
