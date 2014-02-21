#include <iostream>

#include <QDebug>

#include "GUI.h"

GUI::GUI(QObject *parent) :
    QObject(parent)
{
    window = new MainWindow;
    window->show();
}

GUI::~GUI()
{
    delete window;
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
    window->showSatusMassage(msg);
}
