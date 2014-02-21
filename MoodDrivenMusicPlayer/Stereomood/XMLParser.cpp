#include "xmlparser.h"

XMLParser::XMLParser(){}

/*-------------------------------------------------------
                    <Max Felinger>

1) Prove that the given QString has content.
2) Convert QString to QXmlStreamReader.
3) The while loop goes thru the whole xml until the end.
4) Parse song tags.
5) Forward to GUI.
6) Exception handling and clear the QXmlStreamReader object.
---------------------------------------------------------*/
QVector<Song> XMLParser::parseXML(QString xmlAsString) {
    QVector<Song> playlist;

    if (
            xmlAsString.isNull() == false &&
            xmlAsString.isEmpty() == false &&
            xmlAsString.size() > 0
    ) {
        QXmlStreamReader xml(xmlAsString);

        while(!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if(token == QXmlStreamReader::StartElement) {
                if(xml.name() == "song") {
                    playlist.append(this->parseSong(xml));
                }
            }
        }

        if (xml.hasError()) {
            //gui->showStatusMassage("Error parsing xml. Message: " + xml.errorString());
        }
        xml.clear();
    } else {
        //gui->showStatusMassage("No XML given.");
    }

    return playlist;
}

/*-------------------------------------------------------
                    <Max Felinger>

1) Initialize song attributes.
2) Prove that a song tag is given.
3) The while goes thru all child tags of song.
4) Pick the suitable attribute values and save it.
5) Create and return the song object.
---------------------------------------------------------*/
Song XMLParser::parseSong(QXmlStreamReader& xml) {
    int id = -1;
    QString title = "";
    QString artist = "";
    QString image_url = "";
    QString audio_url = "";

    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "song") {
        return Song(-1, "", "", "", "");
    }

    xml.readNext();

    while( !(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "song") ) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            if(xml.name() == "id") {
                xml.readNext();
                id = xml.text().toString().toInt();
            }

            if(xml.name() == "title") {
                xml.readNext();
                title = xml.text().toString();
            }

            if(xml.name() == "artist") {
                xml.readNext();
                artist = xml.text().toString();
            }

            if(xml.name() == "image_url") {
                xml.readNext();
                image_url = xml.text().toString();
            }

            if(xml.name() == "audio_url") {
                xml.readNext();
                audio_url = xml.text().toString();
            }
        }

        /* next attribute */
        xml.readNext();
    }
    return Song(id, title, artist, image_url, audio_url);
}
