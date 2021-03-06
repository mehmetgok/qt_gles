#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "clsChrono.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionDraw_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    clsChrono krono;


    double *signalData;
};

#endif // MAINWINDOW_H
