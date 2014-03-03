#ifndef EPOCWORKER_H
#define EPOCWORKER_H

#include <QString>
#include <QObject>
#include <QThread>

#include "Model/Mood.h"
#include "edk.h"
#include "edkErrorCode.h"
#include "EmoStateDLL.h"

#define EMOCOMPOSER_ADDRESS "127.0.0.1"
#define EMOCOMPOSER_PORT    1726

#define EXCITEMENTSHORTTERMLIMIT 0.69
#define EXCITEMENTLONGTERMLIMIT  1.0
#define ENGAGEMENTLIMIT          0.51
#define BOREDOMLIMIT             0.5

/**
 * @brief The EpocHandler class
 */
class EpocWorker : public QObject
{
    Q_OBJECT
public:
    explicit EpocWorker(QObject *parent = 0);
    virtual ~EpocWorker();

signals:
    void connectionChanged(bool);
    void moodChanged(Mood);

public slots:
    void setDetectionSuite(unsigned int);
    void connect(unsigned int);
    //void addUser();
    void monitorEmotionState();
    void disconnect();

private:
    QThread *thread;
    unsigned int detectionSuite;
    unsigned int userID;
    bool connected;
    EmoEngineEventHandle emoEvent;
    EmoStateHandle emoState;
    Mood lastMood;

    void addUser();
    void createCache();
    void clearCache();
};

#endif // EPOCWORKER_H
