#ifndef REQURL_H
#define REQURL_H

#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <iostream>

#include <QString>

using namespace std;

class ReqURL{
public:
    ReqURL();
    QString setMood(QString mood);
private:
    time_t timer;

    QString baseURL;
    QString questionMark;

    QString moodName;
    QString moodValue;

    QString typeName;
    QString typeValue;

    QString consumerKeyName;
    QString consumerKeyValue;

    QString tokenName;
    QString tokenValue;

    QString sigMethodName;
    QString sigMethodValue;

    QString sigName;
    QString sigValue;

    QString timestampName;
    QString timestampValue;

    QString nonceName;
    QString nonceValue;      // Random value for every request. To avoid replay attacks.

    QString buildURL();
};

#endif // REQURL_H
