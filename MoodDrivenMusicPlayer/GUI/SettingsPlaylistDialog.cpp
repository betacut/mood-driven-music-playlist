#include "SettingsPlaylistDialog.h"
#include "ui_settingsplaylistdialog.h"

SettingsPlaylistDialog::SettingsPlaylistDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::PlaylistConfDialog)
{
    ui->setupUi(this);
}

SettingsPlaylistDialog::~SettingsPlaylistDialog()
{
    delete ui;
}

QVector<Song>& SettingsPlaylistDialog::getMoodPlaylist(Mood mood) {
    switch (mood) {
        case Mood::EXCITEMENT:  return excitementList;  break;
        case Mood::ENGAGEMENT:  return engagementList;  break;
        case Mood::BOREDOM:     return boredomList;     break;
        //case Mood::MEDITATION:  return meditationList;  break;
        //case Mood::FRUSTRATION: return frustrationList; break;
        default: break;
    }
}

QVector<Song>& SettingsPlaylistDialog::getCurrentList()
{
    if (ui->excitement_radioButton->isChecked()) {
        return excitementList;
    } else if (ui->engagement_radioButton->isChecked()) {
        return engagementList;
    } else if (ui->boredom_radioButton->isChecked()) {
        return boredomList;
    }
    /*
    else if (ui->meditation_radioButton->isChecked()) {
        return meditationList;
    } else if (ui->frustration_radioButton->isChecked()) {
        return frustrationList;
    }
    */
}

void SettingsPlaylistDialog::on_addSong_Button_clicked()
{
    QVector<Song> &currentPlaylist = getCurrentList();
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open File"), "/path/to/file/", tr("Mp3 Files (*.mp3)"));

    QRegExp rx("(\\/|\\.mp3)");
    for (int i=0; i<files.size(); i++) {
        QString file = files.at(i);
        QStringList query = file.split(rx);
        query.removeLast(); // remove ".mp3"
        QString fileName = query.last();

        QString artist = "";
        QString title = "";
        query = fileName.split("(\\ - )");
        if (query.size() > 1) {
            artist = query.first();
        }
        title = query.last();
        currentPlaylist.append(Song(currentPlaylist.size() + i, title, artist, "", file));
        ui->song_listWidget->addItem(fileName);

        qDebug() << "Add file to playlist: " << fileName;
    }
}

void SettingsPlaylistDialog::on_deleteSong_Button_clicked()
{
    // Remove selected file from playlist
    if (ui->song_listWidget->currentItem()) {
        QString fileName = ui->song_listWidget->currentItem()->text();
        qDebug() << "Remove file from playlist: " << fileName;

        int index = ui->song_listWidget->row(ui->song_listWidget->currentItem());
        getCurrentList().removeAt(index);
        delete ui->song_listWidget->currentItem();
    }
}

void SettingsPlaylistDialog::on_apply_Button_clicked()
{
    this->hide();
    emit playlistsChanged();
}

void SettingsPlaylistDialog::on_excitement_radioButton_clicked()
{
    ui->song_listWidget->clear();
    foreach (Song song, excitementList) {
        ui->song_listWidget->addItem(song.getTitle());
    }
}

void SettingsPlaylistDialog::on_engagement_radioButton_clicked()
{
    ui->song_listWidget->clear();
    foreach (Song song, engagementList) {
        ui->song_listWidget->addItem(song.getTitle());
    }
}

void SettingsPlaylistDialog::on_boredom_radioButton_clicked()
{
    ui->song_listWidget->clear();
    foreach (Song song, boredomList) {
        ui->song_listWidget->addItem(song.getTitle());
    }
}

/*
void SettingsPlaylistDialog::on_meditation_radioButton_clicked()
{
    ui->song_listWidget->clear();
    foreach (Song song, meditationList) {
        ui->song_listWidget->addItem(song.getTitle());
    }
}

void SettingsPlaylistDialog::on_frustration_radioButton_clicked()
{
    ui->song_listWidget->clear();
    foreach (Song song, frustrationList) {
        ui->song_listWidget->addItem(song.getTitle());
    }
}
*/
