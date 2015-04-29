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
    pdsfjob.cpp

HEADERS  += pdsfmonitormain.h \
    nersclogindata.h \
    nersclogindialog.h \
    newtrequest.h \
    nerscjobdata.h \
    pdsfjob.h

FORMS    += pdsfmonitormain.ui \
    nersclogindialog.ui

unix: CONFIG += link_pkgconfig

unix|win32: LIBS += -lcurl


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../opt/local/lib/release/ -ljsoncpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../opt/local/lib/debug/ -ljsoncpp
else:unix: LIBS += -L/opt/local/lib/ -ljsoncpp

INCLUDEPATH += /opt/local/include
DEPENDPATH += /opt/local/include
