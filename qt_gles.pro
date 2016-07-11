#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T10:16:25
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_gles
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clsChrono.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    clsChrono.h \
    glwidget.h

FORMS    += mainwindow.ui




linux-beaglebone-g++ {
    message("* Using ARM compiler. *")

    target.path = /home/ubuntu
    INSTALLS += target

}

DISTFILES +=
