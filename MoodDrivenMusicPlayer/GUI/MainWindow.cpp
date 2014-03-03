#include <ctime>

#include "Utility/Logger.h"
#include "mainwindow.h"

const QString MainWindow::DEFAULT_IMAGE_STR = ":/images/Resources/cover_missing.png";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), prevItem(NULL), musicSource(MainWindow::LOCAL)
{
    ui->setupUi(this);

    // Set the default song cover
    ui->image_cover->setPixmap(QPixmap(MainWindow::DEFAULT_IMAGE_STR));

    // Configure the emotiv engine action
    QActionGroup* emoEngineTypeGroup = new QActionGroup(this);
    ui->actionTo_EmoEngine->setActionGroup(emoEngineTypeGroup);
    ui->actionTo_EmoComposer->setActionGroup(emoEngineTypeGroup);

    // Configure the music source action
    QActionGroup* playlistTypeGroup = new QActionGroup(this);
    ui->actionLocal->setActionGroup(playlistTypeGroup);
    ui->actionStereomood->setActionGroup(playlistTypeGroup);

    // Create the playlist configuration dialog
    pConf = new SettingsPlaylistDialog;

    // Play the changed playlists
    connect(pConf, SIGNAL(playlistsChanged()),
            this, SLOT(changePlaylist()));

    /**
     * NOTE:    QTMultimedia Module + -dev
     *          libpulse-dev
     */

    // Create the music player
    qPlaylist = new QMediaPlaylist;
    qPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    //qPlaylist->setPlaybackMode(QMediaPlaylist::Random);

    player = new QMediaPlayer;
    player->setPlaylist(qPlaylist);

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
    delete qPlaylist;

    delete pConf;
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
    updateSongInfo();
}

/**
 * @brief MainWindow::slot_playerMediaStatusChanged
 * @param status
 */
void MainWindow::slot_playerMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << "[STATUS] Player Media: " << status;

    if (status == QMediaPlayer::LoadingMedia) {
        ui->label_mediastate->setText("Loading...");
    } else if (status == QMediaPlayer::LoadedMedia) {

    } else if (status == QMediaPlayer::StalledMedia) {
        ui->label_mediastate->setText("Stalled...");
    } else if (status == QMediaPlayer::BufferedMedia) {
        ui->label_mediastate->setText("Ready");
        if (player->state() == QMediaPlayer::PlayingState)
            ui->label_mediastate->setText("Playing");
        else
            ui->label_mediastate->setText("Ready");
    } else if (status == QMediaPlayer::InvalidMedia) {
        ui->label_mediastate->setText("Error");
        //qPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        //player->stop();
    } else if (status == QMediaPlayer::NoMedia) {
        ui->label_mediastate->setText("No Media");
    } else {
        ui->label_mediastate->setText("");
    }
}

/**
 * @brief MainWindow::slot_playerStateChanged
 * @param state
 */
void MainWindow::slot_playerStateChanged(QMediaPlayer::State state)
{
    qDebug() << "[STATUS] Player State: " << state;

    if (state == QMediaPlayer::PlayingState) {
        ui->button_play->setText("Pause");
        ui->label_mediastate->setText("Playing");
    } else if (state == QMediaPlayer::PausedState) {
        ui->button_play->setText("Play");
        ui->label_mediastate->setText("Paused");
    } else if (state == QMediaPlayer::StoppedState) {
        ui->button_play->setText("Play");
        ui->label_mediastate->setText("Stopped");
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
    int currentIndex = qPlaylist->currentIndex();
    Song currentSong = playlist.at(currentIndex);
    if (currentSong.getImageURL().size()) this->loadImage(currentSong.getImageURL());
    QListWidgetItem* item = ui->listWidged_playlist->item(currentIndex);
    if (item) {
        if (prevItem) prevItem->setBackgroundColor(QColor(255, 255, 255));
        item->setBackgroundColor(QColor(255, 100, 100));
        ui->listWidged_playlist->scrollToItem(item, QAbstractItemView::PositionAtCenter);
        prevItem = item;
    }
}

/**
 * @brief MainWindow::changePlaylist
 * @param mood
 */
void MainWindow::changePlaylist()
{
    // Only play changed playlist if local source
    if (musicSource == LOCAL) playPlaylist(currentMood);
}

/**
 * @brief MainWindow::playChoosePlaylist
 * @param mood
 */
void MainWindow::playPlaylist(Mood mood) {

    if (mood == Mood::UNKNOWN) return;

    // Stop and clear the previous playlist
    player->stop();
    qPlaylist->clear();
    ui->listWidged_playlist->clear();
    prevItem = NULL;

    if (musicSource == LOCAL) {
        playlist = pConf->getMoodPlaylist(mood);
        if (playlist.isEmpty()) {
            this->showStatusMassage("Please first add songs for mood: " + mood.toString());
            return;
        }
    }

    // Fill new media playlist
    foreach (Song song, playlist) {
        qDebug() << "Add song: " << "ID=" << song.getId() << ", Title=" << song.getTitle() << ", Artist=" << song.getArtist() << ", Audio URL=" << song.getAudioURL();

        if (musicSource == LOCAL) qPlaylist->addMedia(QUrl::fromLocalFile(song.getAudioURL()));
        else                      qPlaylist->addMedia(QNetworkRequest(song.getAudioURL()));
        ui->listWidged_playlist->addItem(song.getName());
    }
    //qPlaylist->shuffle();
    player->play();
}

/*******************PUBLIC-METHODS***********************/

/**
 * @brief MainWindow::setEmoConnection
 * @param connection
 */
void MainWindow::setEmoConnection(bool connection)
{
    if (connection) ui->label_engineStatus->setText("Connected to Emotiv Engine");
    else            ui->label_engineStatus->setText("Not connected to Emotiv Engine");

    setEmoControls(connection);
}

/**
 * @brief MainWindow::setMood
 * @param mood
 */
void MainWindow::setMood(Mood mood) {

    if (mood == currentMood) return;

    // Set mood image and text
    QPixmap img;
    if (img.load(":/images/Resources/" + mood.toString() + ".png")) {
        //ui->image_mood->setPixmap(img.scaled(50, 50));
        ui->image_mood->setPixmap(img);
    } else {
        showStatusMassage("Error loading image: "+ mood.toString() + ".png");
    }
    //ui->label_mood->setText(mood.toString());

    // Get playlist (local or remote)
    if (musicSource == LOCAL)
        this->playPlaylist(mood);
    else
        emit playlistRequested(mood);

    currentMood = mood;
}

/**
 * @brief MainWindow::setPlaylist
 * @param pl
 */
void MainWindow::setPlaylist(QVector<Song> _playlist)
{
    //if (musicSource == LOCAL) return;
    playlist = _playlist;
    this->playPlaylist(currentMood);
}

/**
 * @brief MainWindow::setEmoControls
 * @param connected
 */
void MainWindow::setEmoControls(bool connected)
{
    if (connected)
    {
        ui->btn_connect->setDisabled(true);
        ui->btn_disconnect->setEnabled(true);
    }
    else
    {
        ui->btn_connect->setEnabled(true);
        ui->btn_disconnect->setDisabled(true);
    }
}

/**
 * @brief MainWindow::showStatusMassage
 * @param msg
 */
void MainWindow::showStatusMassage(QString msg) {
    ui->statusBar->showMessage(msg);
}


/***************************CLICK-HANDLER********************************/

/* Exit application */
void MainWindow::on_actionClose_triggered()
{
    QCoreApplication::quit();
}

/* Choose engine type */
void MainWindow::on_actionTo_EmoEngine_toggled(bool toggled)
{
    if (toggled) {
        qDebug() << "[Click] EmoEngine";
    }
    else {
        qDebug() << "[Click] EmoComposer";
    }

    ui->btn_connect->setDisabled(true);
    ui->btn_disconnect->setDisabled(true);

    emit disconnectRequested();
}

/* Open configuration dialog */
void MainWindow::on_actionSet_Playlist_triggered()
{
    pConf->show();
}

/* Choose music source */
void MainWindow::on_actionLocal_toggled(bool toggled)
{
    if (toggled)
        qDebug() << "[Click] Local";
    else
        qDebug() << "[Click] Stereomood";

    // Clear the previous playlist
    playlist.clear();

    // Set the default song cover
    ui->image_cover->setPixmap(QPixmap(MainWindow::DEFAULT_IMAGE_STR));

    // Set source for playlist
    musicSource = (toggled) ? LOCAL : STEREOMOOD;

    // Get playlist (local or remote)
    if (musicSource == LOCAL)
        this->playPlaylist(currentMood);
    else
        emit playlistRequested(currentMood);
}

/* Connect to or disconnect from emotiv engine */
void MainWindow::on_btn_connect_clicked()
{
    qDebug() << "[Click] Connect Engine";

    ui->btn_connect->setDisabled(true);
    ui->btn_disconnect->setDisabled(true);

    if (this->ui->actionTo_EmoEngine->isChecked())
        emit connectRequested(0);
    else
        emit connectRequested(1);
}

/* Disconnect from emotive engine */
void MainWindow::on_btn_disconnect_clicked()
{
    qDebug() << "[Click] Disconnect Engine";

    ui->btn_connect->setDisabled(true);
    ui->btn_disconnect->setDisabled(true);

    emit disconnectRequested();
}

/* Play/Pause song */
void MainWindow::on_button_play_clicked()
{
    if(qPlaylist->isEmpty()) return;

    if (player->state() == QMediaPlayer::PlayingState) {
        qDebug() << "[Click] Pause Music";
        player->pause();
    }
    else if (player->state() == QMediaPlayer::PausedState ||
             player->state() == QMediaPlayer::StoppedState) {
        qDebug() << "[Click] Play Music";
        player->play();
    }
}

/* Play previous song */
void MainWindow::on_button_prev_clicked()
{
    qDebug() << "[Click] Previous Song";
    qPlaylist->previous();
}

/* Play next song */
void MainWindow::on_button_next_clicked()
{
    qDebug() << "[Click] Next Song";
    qPlaylist->next();
}

/* Switch to next mood */
void MainWindow::on_btn_moodFlip_clicked()
{
    qDebug() << "[Click] Mood Flip";

    // Swtich to next mood
    std::time_t timestamp = std::time(0);
    Mood nextMood(
        // Next mood type
        static_cast<Mood::Type>(currentMood+1),
        // Power
        1,
        // Current timestamp
        timestamp,
        // Manually
        true
    );
    setMood(nextMood);

    // Log event
    Logger::getInstance() << nextMood;
}
