#ifndef REQHANDLER_H
#define REQHANDLER_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>

#include "Model/Mood.h"
#include "Stereomood/requrl.h"
#include "Stereomood/xmlparser.h"

class ReqHandler : public QObject
{
    Q_OBJECT
public:
    explicit ReqHandler(QObject *parent = 0);
    virtual ~ReqHandler();

signals:
    void statusChanged(QString);
    void playlistChanged(QVector<Song>);

public slots:
    void execRequest(Mood mood);

private:
    QNetworkAccessManager* nam;
    ReqURL reqURL;
    XMLParser xmlParser;
    QVector<Song> playlist;

private slots:
    void replyFinished (QNetworkReply *reply);
};

#endif // REQHANDLER_H
