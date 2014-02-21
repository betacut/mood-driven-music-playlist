#-------------------------------------------------
#
# Project created by QtCreator 2014-02-13T16:19:15
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MoodDrivenMusicPlayer
TEMPLATE = app

HEADERS += GUI/GUI.h \
    GUI/MainWindow.h \
    Stereomood/ReqHandler.h \
    Stereomood/ReqURL.h \
    Stereomood/Song.h \
    Stereomood/XMLParser.h
HEADERS +=
HEADERS += Epoc/edk.h Epoc/edkErrorCode.h Epoc/EmoStateDLL.h Epoc/EpocWorker.h

SOURCES += main.cpp \
    GUI/MainWindow.cpp \
    Stereomood/ReqHandler.cpp \
    Stereomood/ReqURL.cpp \
    Stereomood/Song.cpp \
    Stereomood/XMLParser.cpp
SOURCES += GUI/GUI.cpp
SOURCES +=
SOURCES += Epoc/EpocWorker.cpp

# Link the emotiv epoc library
LIBS += -Llib/ -ledk

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc
