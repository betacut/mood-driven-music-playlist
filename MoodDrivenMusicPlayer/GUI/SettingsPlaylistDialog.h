#ifndef PLAYLISTCONFDIALOG_H
#define PLAYLISTCONFDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QVector>
#include <QString>
#include <QDebug>

#include "Model/Mood.h"
#include "Model/Song.h"

namespace Ui {
    class PlaylistConfDialog;
}

class SettingsPlaylistDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsPlaylistDialog(QWidget *parent = 0);
    ~SettingsPlaylistDialog();

    QVector<Song>& getMoodPlaylist(Mood);

signals:
    void playlistsChanged();

private:
    QVector<Song>& getCurrentList();
    
private slots:
    void on_addSong_Button_clicked();
    void on_deleteSong_Button_clicked();
    void on_apply_Button_clicked();
    void on_excitement_radioButton_clicked();
    void on_engagement_radioButton_clicked();
    void on_boredom_radioButton_clicked();
    //void on_meditation_radioButton_clicked();
    //void on_frustration_radioButton_clicked();

private:
    Ui::PlaylistConfDialog *ui;
    QVector<Song> excitementList;
    QVector<Song> engagementList;
    QVector<Song> boredomList;
    //QVector<Song> meditationList;
    //QVector<Song> frustrationList;
};

#endif // PLAYLISTCONFDIALOG_H
