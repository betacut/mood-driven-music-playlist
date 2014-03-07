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

HEADERS += \
    GUI/MainWindow.h \
    GUI/SettingsPlaylistDialog.h \
    Model/Mood.h \
    Model/Song.h \
    Stereomood/ReqHandler.h \
    Stereomood/ReqURL.h \
    Stereomood/XMLParser.h \
    Epoc/edk.h \
    Epoc/edkErrorCode.h \
    Epoc/EmoStateDLL.h \
    Epoc/EpocWorker.h \
    Utility/Logger.h \
    Utility/tinyxml2.h \
    GUI/StatusConsole.h

SOURCES += main.cpp \
    GUI/MainWindow.cpp \
    GUI/SettingsPlaylistDialog.cpp \
    Model/Song.cpp \
    Model/Mood.cpp \
    Stereomood/ReqHandler.cpp \
    Stereomood/ReqURL.cpp \
    Stereomood/XMLParser.cpp \
    Epoc/EpocWorker.cpp \
    Utility/Logger.cpp \
    Utility/tinyxml2.cpp \
    GUI/StatusConsole.cpp

# Link the emotiv epoc library
LIBS += -Llib/ -ledk

FORMS += GUI/mainwindow.ui \
    GUI/settingsplaylistdialog.ui \
    GUI/statusconsole.ui

RESOURCES += \
    Resources.qrc
