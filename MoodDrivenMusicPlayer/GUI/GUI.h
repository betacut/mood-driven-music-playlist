#ifndef GUI_H
#define GUI_H

#include <QObject>

#include "Epoc/EpocWorker.h"
#include "GUI/mainwindow.h"

class GUI : public QObject
{
    Q_OBJECT
private:
    MainWindow* window;

public:
    explicit GUI(QObject *parent = 0);
    virtual ~GUI();

signals:
    void detectionSuiteChanged(unsigned int);
    void connectRequested(unsigned int);
    void disconnectRequested();

public slots:
    void setEmoConnection(bool);
    void setMood(QString);
    void setPlaylist(QVector<Song> playlist);
    void showStatusMassage(QString msg);
};

#endif // GUI_H
