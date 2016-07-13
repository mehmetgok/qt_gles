#include "mainwindow.h"
#include "ui_mainwindow.h"

 #define M_PI       3.14159265358979323846   // pi

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    signalData = new double[2000];

    double samplingRate = 10000.0;



    for (int i=0;i<2000; i++)
    {
        signalData[i] = 5.0*sin(2.0*M_PI*50.0*i/samplingRate);
    }

}

MainWindow::~MainWindow()
{

    delete signalData;


    delete ui;


}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionDraw_triggered()
{
    krono.startChrono();

    ui->widSignal->setData(signalData);
    ui->widSignal->updateGraph = true;
    ui->widSignal->update();

    qDebug("usec: %f", krono.getElapsed_us());
}

void MainWindow::on_pushButton_clicked()
{
    ui->widSignal->setOrhto();
}
