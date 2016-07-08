#include "mainwindow.h"
#include <QApplication>

#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QSurfaceFormat fmt;
     fmt.setDepthBufferSize(24);
     if (QCoreApplication::arguments().contains(QStringLiteral("--multisample")))
         fmt.setSamples(4);
     if (QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"))) {
         fmt.setVersion(2, 0);
         fmt.setProfile(QSurfaceFormat::CoreProfile);
     }
     QSurfaceFormat::setDefaultFormat(fmt);



    MainWindow w;
    w.show();

    return a.exec();
}
