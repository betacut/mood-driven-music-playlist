#include "mainwindow.h"

const QString MainWindow::DEFAULT_IMAGE_STR = ":/images/Resources/cover_missing.png";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), prevItem(NULL)
{
    ui->setupUi(this);
    ui->image_cover->setPixmap(QPixmap(MainWindow::DEFAULT_IMAGE_STR));

    /**
     * NOTE:    QTMultimedia Module + -dev
     *          libpulse-dev
     */

    qPlaylist = new QMediaPlaylist;
    player    = new QMediaPlayer;

    // Error condition has occurred
    connect(player, SIGNAL(error(QMediaPlayer::Error)),
            this, SLOT(slot_playerErrorOccured(QMediaPlayer::Error)));

    // Active media content changed
    connect(player, SIGNAL(currentMediaChanged(const QMediaContent &)),
            this, SLOT(slot_playerMediaChanged(const QMediaContent&)));

    // Current media stream changed
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(slot_playerMediaStatusChanged(QMediaPlayer::MediaStatus)));

    // Playback state property is altered
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(slot_playerStateChanged(QMediaPlayer::State)));

    m_netwManager = new QNetworkAccessManager(this);
    connect(m_netwManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slot_netwManagerFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete m_netwManager;

    player->stop();
    delete player;

    qPlaylist->clear();
    delete qPlaylist;

    delete ui;
}


/*******************************SLOT-METHODS*************************************/

/**
 * @brief MainWindow::slot_netwManagerFinished
 * @param reply
 */
void MainWindow::slot_netwManagerFinished(QNetworkReply *reply)
{
    QPixmap pixmap;

    // Network Error occured
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "[NETWORK] " << reply->errorString();
        pixmap.load(MainWindow::DEFAULT_IMAGE_STR);
    } else {
        pixmap.loadFromData(reply->readAll());
        pixmap = pixmap.scaled(175, 175);
    }
    ui->image_cover->setPixmap(pixmap);
}

/**
 * @brief MainWindow::slot_playerErrorOccured
 * @param Error
 */
void MainWindow::slot_playerErrorOccured(QMediaPlayer::Error error)
{
    qWarning() << "[ERROR] Media player error: " << error;
    qWarning() << "[ERROR] error description: " << player->errorString();
}

/**
 * @brief MainWindow::slot_playerMediaChanged
 * @param media
 */
void MainWindow::slot_playerMediaChanged(const QMediaContent &media)
{
    this->updateSongInfo();
}

/**
 * @brief MainWindow::slot_playerMediaStatusChanged
 * @param status
 */
void MainWindow::slot_playerMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << status;

    if (status == QMediaPlayer::LoadingMedia) {
        ui->label_mediastate->setText("Loading...");
    } else if (status == QMediaPlayer::StalledMedia) {
        ui->label_mediastate->setText("Stalled..");
    } else if (status == QMediaPlayer::BufferedMedia) {
        ui->label_mediastate->setText("Ready");
    } else if (status == QMediaPlayer::InvalidMedia) {
        ui->label_mediastate->setText("Error");
        //qPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        //player->stop();
    }
}

/**
 * @brief MainWindow::slot_playerStateChanged
 * @param state
 */
void MainWindow::slot_playerStateChanged(QMediaPlayer::State state)
{
    qDebug() << state;

    if (state == QMediaPlayer::PlayingState) {
        ui->button_play->setText("Pause");
    } else if (state == QMediaPlayer::PausedState ||
               state == QMediaPlayer::StoppedState) {
        ui->button_play->setText("Play");
    }
}

/*******************PRIVATE-METHODS***********************/


/**
 * @brief MainWindow::loadImage
 * @param urlString
 */
void MainWindow::loadImage(QString urlString)
{
    m_netwManager->get(QNetworkRequest(QUrl(urlString)));
}

/**
 * @brief MainWindow::updateSongInfo
 */
void MainWindow::updateSongInfo()
{
    if (qPlaylist->currentMedia().isNull()) return;

    // Find the current song
    foreach (Song song, playlist) {
        if (qPlaylist->currentMedia().canonicalUrl().toString().contains(QString::number(song.getId())))
        {
            this->loadImage(song.getImageURL());

            QList<QListWidgetItem *> item = ui->listWidged_playlist->findItems(song.getArtist() + " - " + song.getTitle(), Qt::MatchContains);
            if (!item.isEmpty()) {
                if (prevItem) prevItem->setBackgroundColor(QColor(255, 255, 255));
                item.first()->setBackgroundColor(QColor(255, 100, 100));
                ui->listWidged_playlist->scrollToItem(item.first(), QAbstractItemView::PositionAtCenter);
                prevItem = item.first();
            }
        }
    }
}

/*******************PUBLIC-METHODS***********************/

/**
 * @brief MainWindow::setMood
 * @param mood
 */
void MainWindow::setMood(QString mood){
    QPixmap img;
    if (img.load(":/images/Resources/" + mood + ".png")) {
        ui->image_mood->setPixmap(img);
        ui->label_mood->setText(mood);
    } else {
        ui->statusBar->showMessage("Error loading image: "+ mood + ".png");
    }
}

/**
 * @brief MainWindow::setPlaylist
 * @param pl
 */
void MainWindow::setPlaylist(QVector<Song> newPlaylist)
{
    this->playlist = newPlaylist;
    //qDebug() << playlist();

    // Clear the previous playlist
    player->stop();
    qPlaylist->clear();
    ui->listWidged_playlist->clear();
    prevItem = NULL;

    // Fill new media playlist
    foreach (Song song, playlist) {
        qDebug() << "Add song: " << "ID=" << song.getId() << ", Title=" << song.getTitle() << ", Artist=" << song.getArtist() << ", Audio URL=" << song.getAudioURL();

        qPlaylist->addMedia(QNetworkRequest(song.getAudioURL()));
        ui->listWidged_playlist->addItem(song.getArtist() + " - " + song.getTitle());
    }

    qPlaylist->shuffle();
    player->setPlaylist(qPlaylist);
    player->play();
}

/**
 * @brief MainWindow::showSatusMassage
 * @param msg
 */
void MainWindow::showSatusMassage(QString msg) {
    ui->statusBar->showMessage(msg);
}


/***************************CLICK-HANDLER********************************/

void MainWindow::on_button_play_clicked()
{
    if (player->state() == QMediaPlayer::PlayingState) {
        qDebug() << "[Pressed] pause";
        player->pause();
    }
    else if (player->state() == QMediaPlayer::PausedState ||
             player->state() == QMediaPlayer::StoppedState) {
        qDebug() << "[Pressed] play";
        player->play();
    }
}

void MainWindow::on_button_next_clicked()
{
    qDebug() << "[Pressed] next";
    qPlaylist->next();
}

void MainWindow::on_button_prev_clicked()
{
    qDebug() << "[Pressed] previous";
    qPlaylist->previous();
}
