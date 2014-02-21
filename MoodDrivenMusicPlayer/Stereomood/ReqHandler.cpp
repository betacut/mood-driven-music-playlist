#include "ReqHandler.h"

ReqHandler::ReqHandler(QObject *parent) :
    QObject(parent) {}

ReqHandler::~ReqHandler() {}

/*-------------------------------------------------------
                    <Max Felinger>

1) Create url with given mood.
2) Set mood for gui.
2) Create QNetworkAccessManager object
3) Connect sender object to receiver method
4) Execute request
---------------------------------------------------------*/
void ReqHandler::execRequest(QString mood){

    QString urlAsString = reqURL.setMood(mood);
    QUrl url(urlAsString.toStdString().c_str());

    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    nam->get(QNetworkRequest(url));

    qDebug() << "[NETWORK] Send stereomood request: " << url.toString();
}

/*-------------------------------------------------------
                    <Max Felinger>

1) Catch error.
2) Process response
    a) Read data
    b) Convert to QString
    c) Forward to parse
---------------------------------------------------------*/
void ReqHandler::replyFinished (QNetworkReply *reply) {
    if (reply->error()) {
        emit statusChanged(reply->errorString());
        reply->deleteLater();        
    } else {
        QByteArray bytes = reply->readAll();
        reply->deleteLater();

        QString response(bytes);
        qDebug() << "[NETWORK] Got stereomood response: " << response;

        playlist = xmlParser.parseXML(response);
        if (playlist.size() > 0) {
            emit playlistChanged(playlist);
        } else {
            emit statusChanged("Empty playlist after parsing XML.");
        }
    }
}
