#include "SettingsPlaylistDialog.h"
#include "ui_settingsplaylistdialog.h"

SettingsPlaylistDialog::SettingsPlaylistDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::SettingsPlaylistDialog)
{
    ui->setupUi(this);

    // Set the filename to save the playlist to
    playlistFilePath = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + "/" + XML_PLAYLIST_FILENAME);
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
}

Song SettingsPlaylistDialog::getSongFromPath(QString file, int songID=0)
{
    QString fileName = getFilenameFromPath(file);
    QStringList query = fileName.split("(\\ - )");
    QString artist = "";
    QString title = "";
    if (query.size() > 1) {
        artist = query.first();
    }
    title = query.last();

    return Song(songID, title, artist, "", file);
}

QString SettingsPlaylistDialog::getFilenameFromPath(QString file)
{
    QRegExp rx("(\\/|\\.mp3)");
    QStringList query = file.split(rx);
    query.removeLast(); // remove ".mp3"
    return query.last();
}

void SettingsPlaylistDialog::loadPlaylistsFromXML()
{
    tinyxml2::XMLDocument playlistFile;
    tinyxml2::XMLError error = playlistFile.LoadFile(playlistFilePath.toStdString().c_str());
    //qDebug() << "LoadFile CODE:" << error;

    // File loaded
    if (error == 0) {
        tinyxml2::XMLElement* element = playlistFile.FirstChildElement(Mood(Mood::EXCITEMENT, 0, 0, false).toString().toStdString().c_str());
        if (element) {
            tinyxml2::XMLElement* para = element->FirstChildElement(XML_PATH_TAG);
            while (para) {
                //excitementList += para->GetText();
                excitementList.append(this->getSongFromPath(para->GetText()));

                // Add to the list widget if selected
                if (ui->excitement_radioButton->isChecked())
                    ui->song_listWidget->addItem(this->getFilenameFromPath(para->GetText()));

                para = para->NextSiblingElement(XML_PATH_TAG);
            }
        } else {
            qDebug() << "Error loading EXCITEMENT List";
        }

        element = playlistFile.FirstChildElement(Mood(Mood::ENGAGEMENT, 0, 0, false).toString().toStdString().c_str());
        if (element) {
            tinyxml2::XMLElement* para = element->FirstChildElement(XML_PATH_TAG);
            while (para) {
                engagementList.append(this->getSongFromPath(para->GetText()));

                // Add to the list widget if selected
                if (ui->engagement_radioButton->isChecked())
                    ui->song_listWidget->addItem(this->getFilenameFromPath(para->GetText()));
                para = para->NextSiblingElement(XML_PATH_TAG);
            }
        } else {
            qDebug() << "Error loading ENGAGEMENT List";
        }

        element = playlistFile.FirstChildElement(Mood(Mood::BOREDOM, 0, 0, false).toString().toStdString().c_str());
        if (element) {
            tinyxml2::XMLElement* para = element->FirstChildElement(XML_PATH_TAG);
            while (para) {
                boredomList.append(this->getSongFromPath(para->GetText()));

                // Add to the list widget if selected
                if (ui->boredom_radioButton->isChecked())
                    ui->song_listWidget->addItem(this->getFilenameFromPath(para->GetText()));
                para = para->NextSiblingElement(XML_PATH_TAG);
            }
        } else {
            qDebug() << "Error loading BOREDOM List";
        }
    }
}

void SettingsPlaylistDialog::on_addSong_Button_clicked()
{
    QVector<Song> &currentPlaylist = getCurrentList();
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open File"), "/path/to/file/", tr("Mp3 Files (*.mp3)"));

    for (int i=0; i<files.size(); i++) {
        currentPlaylist.append(this->getSongFromPath(files.at(i), currentPlaylist.size() + i));
        QString fileName = this->getFilenameFromPath(files.at(i));
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
//        getCurrentList().removeAt(index);
        getCurrentList().remove(index);
        delete ui->song_listWidget->currentItem();
    }
}

/* Save selected music files to xml playlist file */
void SettingsPlaylistDialog::on_apply_Button_clicked()
{
    // Create the document
    tinyxml2::XMLDocument playlistFile;

    // Clear file
    playlistFile.Clear();

    tinyxml2::XMLElement* versionNode = playlistFile.NewElement("Version");
    tinyxml2::XMLText* versionText = playlistFile.NewText("1.0.0");
    versionNode->InsertEndChild(versionText);
    playlistFile.InsertEndChild(versionNode);

    // Add EXCITEMENT Songs to XML
    tinyxml2::XMLElement* playlistElement = playlistFile.NewElement(Mood(Mood::EXCITEMENT, 0, 0, false).toString().toStdString().c_str());
    foreach (Song song, this->excitementList) {
        tinyxml2::XMLElement* pathELement = playlistFile.NewElement(XML_PATH_TAG);
        tinyxml2::XMLText* pathText = playlistFile.NewText(song.getAudioURL().toStdString().c_str());
        pathELement->InsertEndChild(pathText);
        playlistElement->InsertEndChild(pathELement);
    }
    playlistFile.InsertEndChild(playlistElement);

    // Add ENGAGEMENT Songs to XML
    playlistElement = playlistFile.NewElement(Mood(Mood::ENGAGEMENT, 0, 0, false).toString().toStdString().c_str());
    foreach (Song song, this->engagementList) {
        tinyxml2::XMLElement* pathELement = playlistFile.NewElement(XML_PATH_TAG);
        tinyxml2::XMLText* pathText = playlistFile.NewText(song.getAudioURL().toStdString().c_str());
        pathELement->InsertEndChild(pathText);
        playlistElement->InsertEndChild(pathELement);
    }
    playlistFile.InsertEndChild(playlistElement);

    // Add BOREDOM Songs to XML
    playlistElement = playlistFile.NewElement(Mood(Mood::BOREDOM, 0, 0, false).toString().toStdString().c_str());
    foreach (Song song, this->boredomList) {
        tinyxml2::XMLElement* pathELement = playlistFile.NewElement(XML_PATH_TAG);
        tinyxml2::XMLText* pathText = playlistFile.NewText(song.getAudioURL().toStdString().c_str());
        pathELement->InsertEndChild(pathText);
        playlistElement->InsertEndChild(pathELement);
    }
    playlistFile.InsertEndChild(playlistElement);

    // Save the playlist file
    playlistFile.SaveFile(playlistFilePath.toStdString().c_str());

    qDebug() << "Save playlists to " << playlistFilePath.toStdString().c_str();

	// Close dialog
    this->hide();
    
    // Trigger playlists changed event
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
