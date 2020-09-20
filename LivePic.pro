#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T15:36:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LivePic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eden.cpp \
    configfile.cpp \
    picnetwork.cpp \
    stopwatch.cpp \
    qmouselabel.cpp \
    picthread.cpp \
    picthread_processpicture.cpp \
    picthread_processpicture_convolution.cpp \
    picthread_processpicture_hq2x.cpp \
    picthread_processpicture_hq3x.cpp \
    picthread_processpicture_hq4x.cpp \
    winsettings.cpp \
    settings.cpp \
    transformitem.cpp \
    transformcore.cpp \
    picthread_processpicture_convolution_gamma.cpp

HEADERS  += mainwindow.h \
    eden.h \
    configfile.h \
    picnetwork.h \
    stopwatch.h \
    qmouselabel.h \
    picthread.h \
    winsettings.h \
    settings.h \
    transformitem.h \
    transformcore.h

FORMS    += mainwindow.ui \
    winsettings.ui
CONFIG += c++11

