#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>

#include "ui_mainwindow.h"
#include "SettingsPlaylistDialog.h"
#include "Model/Song.h"
#include "Model/Mood.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT    
public:
    enum MusicSource
    {
        LOCAL = 0,
        STEREOMOOD
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setEmoConnection(bool);
    void setMood(Mood);
    void setPlaylist(QVector<Song>);
    void showStatusMassage(QString);

signals:
    void detectionSuiteChanged(unsigned int);
    void playlistRequested(Mood mood);
    void connectRequested(unsigned int);
    void disconnectRequested();

private slots:
    void slot_netwManagerFinished(QNetworkReply *);

    void slot_playerErrorOccured(QMediaPlayer::Error);
    void slot_playerMediaChanged(const QMediaContent &);
    void slot_playerMediaStatusChanged(QMediaPlayer::MediaStatus);
    void slot_playerStateChanged(QMediaPlayer::State);

    void on_btn_connect_clicked();
    void on_btn_disconnect_clicked();
    void on_button_prev_clicked();
    void on_button_next_clicked();
    void on_button_play_clicked();

    void on_actionTo_EmoEngine_toggled(bool toggled);
    void on_actionSet_Playlist_triggered();
    void on_btn_moodFlip_clicked();
    void on_actionClose_triggered();
    void on_actionLocal_toggled(bool arg1);

    void loadImage(QString);
    void updateSongInfo();
    void changePlaylist();
    void switchPlaylist();

private:
    static const QString DEFAULT_IMAGE_STR;

    Ui::MainWindow *ui;
    SettingsPlaylistDialog *pConf;

    QNetworkAccessManager *m_netwManager;
    QMediaPlayer *player;
    QMediaPlaylist *qPlaylist;
    QVector<Song> playlist;
    QListWidgetItem* prevItem;

    MusicSource musicSource;
    Mood currentMood;
    bool switchPlaylistOnSongEnd;

    void setEmoControls(bool);
    void fetchPlaylist();
};

#endif // MAINWINDOW_H
