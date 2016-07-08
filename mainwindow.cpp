#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionDraw_triggered()
{
    krono.startChrono();

    ui->widSignal->updateGraph = true;
    ui->widSignal->update();

    qDebug("usec: %f", krono.getElapsed_us());
}
