#include <iostream>

#include <QDebug>

#include "GUI.h"

GUI::GUI(QObject *parent) :
    QObject(parent)
{
    window = new MainWindow;
    window->show();

    QObject::connect(window, SIGNAL(detectionSuiteChanged(unsigned int)),
            this, SIGNAL(detectionSuiteChanged(unsigned int)));
    QObject::connect(window, SIGNAL(connectRequested(unsigned int)),
            this, SIGNAL(connectRequested(unsigned int)));
    QObject::connect(window, SIGNAL(disconnectRequested()),
            this, SIGNAL(disconnectRequested()));
}

GUI::~GUI()
{
    delete window;
}

void GUI::setEmoConnection(bool connection)
{
    window->setEmoControls(connection);
    if (connection) window->showStatusMassage("Connected to Emotiv Engine. Detect Mood...");
    else            window->showStatusMassage("Not connected to Emotiv Engine");
}

void GUI::setMood(QString newMood)
{    
    window->setMood(newMood);
}

void GUI::setPlaylist(QVector<Song> playlist)
{
    window->setPlaylist(playlist);
}

void GUI::showStatusMassage(QString msg)
{
    window->showStatusMassage(msg);
}
