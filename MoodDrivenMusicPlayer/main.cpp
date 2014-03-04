#include <QApplication>
#include <QMetaObject>
#include <QDebug>

#include "Epoc/EpocWorker.h"
#include "Stereomood/ReqHandler.h"
#include "GUI/MainWindow.h"

/*
 * TODO:
 * - Analyse the excitement value over a long period (how long? song length?)
 * - Speichern und Wiederherstellen der letzten Song Position?
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qDebug() << "Main Thread ID: " << app.thread()->currentThreadId();

    // Create Epoc worker thread to handle EmoEngine
    EpocWorker *epocWorker = new EpocWorker;

    // Create Stereomood Handler
    ReqHandler *reqhandler = new ReqHandler;

    // Create GUI
    MainWindow *window = new MainWindow;

    qRegisterMetaType<Mood>("Mood");

    // Notify GUI when EmoEngine connection changes
    QObject::connect(epocWorker, SIGNAL(connectionChanged(bool)),
                     window, SLOT(setEmoConnection(bool)));

    // Notify GUI when mood changes
    QObject::connect(epocWorker, SIGNAL(moodChanged(Mood)),
                     window, SLOT(setMood(Mood)));

    // Notify Stereomood when mood changes
    QObject::connect(window, SIGNAL(playlistRequested(Mood)),
                     reqhandler, SLOT(execRequest(Mood)));

    // Notify GUI when playlist changes
    QObject::connect(reqhandler, SIGNAL(playlistChanged(QVector<Song>)),
                     window, SLOT(setPlaylist(QVector<Song>)));

    // Notify GUI when network status changes
    QObject::connect(reqhandler, SIGNAL(statusChanged(QString)),
                     window, SLOT(showStatusMassage(QString)));

    // Set the active detection suite
    QObject::connect(window, SIGNAL(detectionSuiteChanged(unsigned int)),
                     epocWorker, SLOT(setDetectionSuite(unsigned int)), Qt::DirectConnection);

    // Establish connection to EmoEngine
    QObject::connect(window, SIGNAL(connectRequested(unsigned int)),
                     epocWorker, SLOT(connect(unsigned int)), Qt::QueuedConnection);
    // Directly monitor emotion state after connection established
    QObject::connect(window, SIGNAL(connectRequested(unsigned int)),
                     epocWorker, SLOT(monitorEmotionState()), Qt::QueuedConnection);

    // Close connection to EmoEngine
    QObject::connect(window, SIGNAL(disconnectRequested()),
                     epocWorker, SLOT(disconnect()), Qt::DirectConnection);

    //QMetaObject::invokeMethod(epocWorker, "connect", Qt::QueuedConnection);
    //QMetaObject::invokeMethod(epocWorker, "addUser", Qt::QueuedConnection);
    //QMetaObject::invokeMethod(epocWorker, "monitorEmotionState", Qt::QueuedConnection);

    // Show GUI
    window->show();

    // Start Application
    app.exec();

    ////// Application Exit Cleanup

    // Disconnect Emotiv Engine
    QMetaObject::invokeMethod(epocWorker, "disconnect", Qt::DirectConnection);

    // Clean memory
    delete epocWorker;
    delete reqhandler;
    delete window;

    return 0;
}
