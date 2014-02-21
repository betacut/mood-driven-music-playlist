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
#include "Stereomood/song.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setMood(QString);
    void setPlaylist(QVector<Song>);
    void setEmoControls(bool);
    void showStatusMassage(QString);

signals:
    void detectionSuiteChanged(unsigned int);
    void connectRequested(unsigned int);
    void disconnectRequested();

private slots:
    void slot_netwManagerFinished(QNetworkReply *);
    void slot_playerErrorOccured(QMediaPlayer::Error);
    void slot_playerMediaChanged(const QMediaContent &);
    void slot_playerMediaStatusChanged(QMediaPlayer::MediaStatus);
    void slot_playerStateChanged(QMediaPlayer::State);
    void loadImage(QString);
    void updateSongInfo();
    void on_radio_detection_toggled(bool);
    void on_btn_connect_clicked();
    void on_btn_disconnect_clicked();
    void on_button_prev_clicked();
    void on_button_next_clicked();
    void on_button_play_clicked();

private:
    static const QString DEFAULT_IMAGE_STR;

    Ui::MainWindow *ui;
    QNetworkAccessManager *m_netwManager;
    QMediaPlayer *player;
    QMediaPlaylist *qPlaylist;
    QVector<Song> playlist;
    QListWidgetItem* prevItem;
};

#endif // MAINWINDOW_H
