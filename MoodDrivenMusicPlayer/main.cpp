#include <QApplication>
#include <QMetaObject>
#include <QDebug>

#include "Epoc/EpocWorker.h"
#include "Stereomood/ReqHandler.h"
#include "GUI/GUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qDebug() << "Main Thread ID: " << app.thread()->currentThreadId();

    // Create Epoc worker thread to handle EmoEngine
    EpocWorker *epocWorker = new EpocWorker;

    // Create Stereomood Handler
    ReqHandler *reqhandler = new ReqHandler;

    // Create GUI
    GUI *gui = new GUI;

    // Notify Stereomood when mood changes
    QObject::connect(epocWorker, SIGNAL(moodChanged(QString)),
                     reqhandler, SLOT(execRequest(QString)));

    // Notify GUI when EmoEngine connection changes
    QObject::connect(epocWorker, SIGNAL(connectionChanged(QString)),
                     gui, SLOT(showStatusMassage(QString)));

    // Notify GUI when mood changes
    QObject::connect(epocWorker, SIGNAL(moodChanged(QString)),
                     gui, SLOT(setMood(QString)));

    // Notify GUI when playlist changes
    QObject::connect(reqhandler, SIGNAL(playlistChanged(QVector<Song>)),
                     gui, SLOT(setPlaylist(QVector<Song>)));

    // Notify GUI when network status changes
    QObject::connect(reqhandler, SIGNAL(statusChanged(QString)),
                     gui, SLOT(showStatusMassage(QString)));

    // Establish connection to EmoEngine
    QMetaObject::invokeMethod(epocWorker, "connect", Qt::QueuedConnection);
    QMetaObject::invokeMethod(epocWorker, "addUser", Qt::QueuedConnection);

    // Check if emotion changes
    QMetaObject::invokeMethod(epocWorker, "monitorEmotionState", Qt::QueuedConnection);

    // Pause or stop monitoring

    /*
    QString mood = "happy";
    ReqHandler reqhandler;
    reqhandler.execRequest(mood);
    */

    // Start Application
    app.exec();

    //////
    // Application Exit Cleanup

    // Disconnect Emotiv Engine
    QMetaObject::invokeMethod(epocWorker, "disconnect", Qt::DirectConnection);

    // Clean memory
    delete epocWorker;
    delete reqhandler;
    delete gui;

    return 0;
}
