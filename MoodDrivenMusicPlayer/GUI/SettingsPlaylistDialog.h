#ifndef PLAYLISTCONFDIALOG_H
#define PLAYLISTCONFDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QVector>
#include <QString>
#include <QDebug>

#include "Model/Mood.h"
#include "Model/Song.h"
#include "Utility/tinyxml2.h"

#define XML_PLAYLIST_FILENAME "playlists.xml"
#define XML_PATH_TAG "path"

namespace Ui {
    class SettingsPlaylistDialog;
}

class SettingsPlaylistDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsPlaylistDialog(QWidget *parent = 0);
    ~SettingsPlaylistDialog();

    QVector<Song>& getMoodPlaylist(Mood);
    void loadPlaylistsFromXML();

signals:
    void playlistsChanged();

private:
    Ui::SettingsPlaylistDialog *ui;
    QString playlistFilePath;
    QVector<Song> excitementList;
    QVector<Song> engagementList;
    QVector<Song> boredomList;

    QVector<Song>& getCurrentList();
    Song getSongFromPath(QString, int);
    QString getFilenameFromPath(QString);
    
private slots:
    void on_addSong_Button_clicked();
    void on_deleteSong_Button_clicked();
    void on_apply_Button_clicked();
    void on_excitement_radioButton_clicked();
    void on_engagement_radioButton_clicked();
    void on_boredom_radioButton_clicked();
};

#endif // PLAYLISTCONFDIALOG_H
