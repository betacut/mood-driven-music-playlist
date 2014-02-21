#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <stdio.h>
#include <iostream>

#include <QXmlStreamReader>
#include <QVector>

#include "GUI/GUI.h"
#include "Stereomood/song.h"

using namespace std;

class XMLParser {
public:
    XMLParser();
    QVector<Song> parseXML(QString xmlAsString);
private:
    Song parseSong(QXmlStreamReader& xml);
};

#endif // XMLPARSER_H
