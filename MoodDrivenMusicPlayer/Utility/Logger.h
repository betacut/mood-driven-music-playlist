#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include <fstream>
#include <iostream>

#include <QString>

#include "Model/Mood.h"

#define LOGGER_FILE "EmoStateLogger.csv"

using namespace std;

/*
 * Singleton Class
 */
class Logger
{
private:
    ofstream* loggerFile;

    Logger();
    Logger(const Logger&);
    ~Logger();
public:
    static Logger& getInstance();
    Logger& operator<<(const Mood&);
};

#endif // LOGGER_H
