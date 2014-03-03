#include <QDate>
#include <QDebug>

#include "Logger.h"

// TODO: Write the count of automatic and manual mood changes?

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

Logger::Logger()
{
    QDate date = QDate::currentDate();
    QString dateStr = date.toString(Qt::ISODate);
    string filename =  dateStr.toStdString() + "_" + LOGGER_FILE;
    qDebug() << "Open Log File: " << filename.c_str();
    loggerFile = new ofstream (filename.c_str(), ios::trunc);

    // Create the top header
    (*loggerFile) << "Timestamp" << ";";
    (*loggerFile) << "Mood" << ";";
    (*loggerFile) << "Power" << ";";
    (*loggerFile) << "Flipped";

    (*loggerFile) << endl;
}

Logger::~Logger()
{
    qDebug() << "Close Log File.";

    loggerFile->close();
    delete loggerFile;
}

Logger& Logger::operator<<(const Mood& mood)
{
    if (loggerFile->is_open()) {

        // Write timestamp
        (*loggerFile) << QString::number(mood.getTimestamp()).toStdString() << ";";

        // Write mood
        (*loggerFile) << mood.toString().toStdString() << ";";

        // Write power
        (*loggerFile) << QString::number(mood.getPower()).toStdString() << ";";

        // Write user or headset triggered
        (*loggerFile) << QString::number(mood.getUserTriggered()).toStdString();

        (*loggerFile) << endl;
    }
    return *this;
}
