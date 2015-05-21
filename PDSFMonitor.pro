#-------------------------------------------------
#
# Project created by QtCreator 2015-02-28T15:30:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PDSFMonitor
TEMPLATE = app


SOURCES += main.cpp\
        pdsfmonitormain.cpp \
    nersclogindata.cpp \
    nersclogindialog.cpp \
    newtrequest.cpp \
    nerscjobdata.cpp \
    pdsfjob.cpp \
    aboutdialog.cpp

HEADERS  += pdsfmonitormain.h \
    nersclogindata.h \
    nersclogindialog.h \
    newtrequest.h \
    nerscjobdata.h \
    pdsfjob.h \
    aboutdialog.h

FORMS    += pdsfmonitormain.ui \
    nersclogindialog.ui \
    detailed.ui \
    aboutdialog.ui

unix: CONFIG += link_pkgconfig

unix|win32: LIBS += -lcurl

OTHER_FILES += \
    gplv3.txt
