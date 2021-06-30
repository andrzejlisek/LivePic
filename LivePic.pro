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
    googleconvert.cpp \
        mainwindow.cpp \
    eden.cpp \
    configfile.cpp \
    picnetwork.cpp \
    picthread_delayline.cpp \
    recorder.cpp \
    stopwatch.cpp \
    qmouselabel.cpp \
    picthread.cpp \
    picthread_processpicture.cpp \
    picthread_processpicture_convolution.cpp \
    picthread_processpicture_hq2x.cpp \
    picthread_processpicture_hq3x.cpp \
    picthread_processpicture_hq4x.cpp \
    textcapture.cpp \
    winrecorder.cpp \
    winsettings.cpp \
    settings.cpp \
    transformitem.cpp \
    transformcore.cpp \
    picthread_processpicture_convolution_gamma.cpp

HEADERS  += mainwindow.h \
    eden.h \
    configfile.h \
    googleconvert.h \
    picnetwork.h \
    recorder.h \
    stopwatch.h \
    qmouselabel.h \
    picthread.h \
    textcapture.h \
    winrecorder.h \
    winsettings.h \
    settings.h \
    transformitem.h \
    transformcore.h

FORMS    += mainwindow.ui \
    winrecorder.ui \
    winsettings.ui
CONFIG += c++17
