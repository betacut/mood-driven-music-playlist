#ifndef EPOCWORKER_H
#define EPOCWORKER_H

// TODO: EmoComposer or Engine
// TODO: Expressiv or Affectiv Suit
// Reconnect

#include <QString>
#include <QObject>
#include <QThread>

#include "edk.h"
#include "edkErrorCode.h"
#include "EmoStateDLL.h"

#define EMOCOMPOSER_ADDRESS "127.0.0.1"
#define EMOCOMPOSER_PORT    1726

typedef enum Mood_enum {
    UNKNOWN = -1, HAPPY, SAD, RELAXED, STRESSED
} Mood;
const QString moodString[] = {"happy","sad","relaxed", "stressed"};

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
    void connectionChanged(QString);
    void moodChanged(QString);

public slots:
    void connect();
    void addUser();
    void monitorEmotionState();
    void disconnect();

private:
    QThread *thread;
    unsigned int userID;
    bool connected;
    EmoEngineEventHandle emoEvent;
    EmoStateHandle emoState;
    Mood lastMood;

    void createCache();
    void clearCache();
};

#endif // EPOCWORKER_H
