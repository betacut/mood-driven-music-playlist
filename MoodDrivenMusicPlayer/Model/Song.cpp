#include "song.h"

Song::Song(){}

/*-------------------------------------------------------
                    <Max Felinger>

1) Initialize constant variables.
---------------------------------------------------------*/
Song::Song(int _id, QString _title, QString _artist, QString _imageURL, QString _audioURL) :
    id(_id), title(_title), artist(_artist), imageURL(_imageURL), audioURL(_audioURL) {}


/*-------------------------------------------------------
                    <Max Felinger>

Getter methods.
---------------------------------------------------------*/
int Song::getId() const {
    return this->id;
}
QString Song::getName() const
{
    return "" + (artist.size() ? artist + " - " : "") + title;
}
QString Song::getArtist() const {
    return this->artist;
}
QString Song::getTitle() const {
    return this->title;
}
QString Song::getImageURL() const {
    return this->imageURL;
}
QString Song::getAudioURL() const {
    return this->audioURL;
}
