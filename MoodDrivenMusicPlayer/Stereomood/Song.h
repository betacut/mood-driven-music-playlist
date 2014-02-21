#ifndef SONG_H
#define SONG_H

#include <QString>

class Song {
public:
    Song();
    Song(int, QString, QString, QString, QString);
    int getId() const;
    QString getTitle() const;
    QString getArtist() const;
    QString getImageURL() const;
    QString getAudioURL() const;

private:
    int id;
    QString title;
    QString artist;
    QString imageURL;
    QString audioURL;
};

#endif // SONG_H
