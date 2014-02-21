#include <iostream>
#include <map>

#include "Epoc/EpocWorker.h"
#include "GUI/GUI.h"

EpocWorker::EpocWorker(QObject *parent) :
    QObject(parent), detectionSuite(0), userID(0), connected(false), lastMood(UNKNOWN)
{
    // Create thread to handle connection to emotiv engine
    thread = new QThread();
    thread->start();
    moveToThread(thread);
}

EpocWorker::~EpocWorker()
{
    thread->exit(0);
    thread->wait();
    delete thread;
}

/*******************
 * Public slots *
 *******************/

void EpocWorker::setDetectionSuite(unsigned int newSuite)
{
    detectionSuite = newSuite;

    qDebug() << "[Emotiv] Detection Suite changed";
}

void EpocWorker::connect(unsigned int connectionType)
{
    switch (connectionType)
    {
        case 0:
        {
            if(EE_EngineConnect() == EDK_OK)
            {
                qDebug() << "Connected to EmoEngine!";
                connected = true;

                qDebug() << "Start receiving mood data!";
                createCache();
            }
            else
            {
                qDebug() << "Could not connect to EmoEngine!";
                connected = false;
            }
        }
        break;
        case 1:
        {
            if(EE_EngineRemoteConnect(EMOCOMPOSER_ADDRESS, EMOCOMPOSER_PORT) == EDK_OK)
            {
                qDebug() << "Connected to EmoComposer!";
                connected = true;

                qDebug() << "Start receiving mood data!";
                createCache();
            }
            else
            {
                qDebug() << "Could not connect to EmoComposer! - " << EMOCOMPOSER_ADDRESS << ":" << EMOCOMPOSER_PORT;
                connected = false;
            }
        }
        break;
        default:
        {
          qWarning() <<"Invalid option!";
        }
        break;
    }

    emit connectionChanged(connected);

    // Notify
    if (connected) addUser();
}

void EpocWorker::addUser()
{
    int eventErrorCode = 0;
    int userErrorCode = 0;
    EE_Event_t eventType;
    bool userAdded;

    while (connected && !userAdded)
    {
        eventErrorCode = EE_EngineGetNextEvent(emoEvent);
        qDebug() << "eventErrorCode " << eventErrorCode;
        if (eventErrorCode == EDK_OK)
        {
            eventType = EE_EmoEngineEventGetType(emoEvent);
            if (eventType == EE_UserAdded)
            {
                userErrorCode = EE_EmoEngineEventGetUserId(emoEvent, &userID);
                std::cout << "User added: " << userID << std::endl;
                userAdded = true;

                // TODO: Error handling?
                //printf("EE_EmoEngineEventGetUserId: %d, Error: %#x\n", userID, userErrorCode);
            }
        }
        else if (eventErrorCode != EDK_NO_EVENT)
        {
            // Error occured -> Stop trying
            emit connectionChanged("Internal error in Emotiv Engine!");
            qDebug() << "Internal error in Emotiv Engine!";
            break;
        }
    }
}

void EpocWorker::monitorEmotionState()
{
    int eventErrorCode = 0;
    EE_Event_t eventType;
    Mood mood;

    while (connected)
    {
        eventErrorCode = EE_EngineGetNextEvent(emoEvent);
        if (eventErrorCode == EDK_OK)
        {
            eventType = EE_EmoEngineEventGetType(emoEvent);

            // Read the EmoState if it has been updated
            if (eventType == EE_EmoStateUpdated)
            {
                // Read EmoState
                EE_EmoEngineEventGetEmoState(emoEvent, emoState);

                // Read timestamp
                const float timestamp = ES_GetTimeFromStart(emoState);
                std::cout <<"New EmoState from user " << userID << " at " << timestamp << std::endl;

                switch (detectionSuite)
                {
                    // Expressiv Suite
                    case 0:
                    {
                        // Read expressiv state
                        std::map<EE_ExpressivAlgo_t, float> expressivStates;
                        EE_ExpressivAlgo_t lowerFaceAction = ES_ExpressivGetLowerFaceAction(emoState);
                        float			   lowerFacePower  = ES_ExpressivGetLowerFaceActionPower(emoState);
                        expressivStates[lowerFaceAction] = lowerFacePower;

                        // Set mood
                        if      (expressivStates[EXP_LAUGH]       >= 1.0) mood = HAPPY;
                        else if (expressivStates[EXP_SMILE]       >= 1.0) mood = RELAXED;
                        else if (expressivStates[EXP_CLENCH]      >= 1.0) mood = STRESSED;
                        else if (expressivStates[EXP_SMIRK_LEFT]  >= 1.0) mood = SAD;
                        else if (expressivStates[EXP_SMIRK_RIGHT] >= 1.0) mood = SAD;
                        else                                              mood = UNKNOWN;
                    }
                    break;

                    // Affectiv Suite
                    case 1:
                    {
                        // Read affectiv state
                        if      (ES_AffectivGetExcitementShortTermScore(emoState) >= 1.0) mood = HAPPY;
                        else if (ES_AffectivGetEngagementBoredomScore(emoState)   >= 1.0) mood = SAD;
                        else if (ES_AffectivGetMeditationScore(emoState)          >= 1.0) mood = RELAXED;
                        else if (ES_AffectivGetFrustrationScore(emoState)         >= 1.0) mood = STRESSED;
                        else                                                              mood = UNKNOWN;
                    }
                    break;
                    default:
                    {

                    }
                    break;
                }

                // Call function to handle mood change
                if (mood != lastMood) {
                    lastMood = mood;
                    emit moodChanged(moodString[mood]);
                }
            }
        }
        else if (eventErrorCode != EDK_NO_EVENT)
        {
            qDebug() << "Internal error in Emotiv Engine!";

            // Error occured -> Stop trying
            emit connectionChanged("Internal error in Emotiv Engine!");
            break;
        }
    }
}

void EpocWorker::disconnect()
{
    if (!connected) return;

    clearCache();

    connected = !(EE_EngineDisconnect() == EDK_OK);

    qDebug() << "EmoEngine disconnected!" << endl;

    emit connectionChanged(false);
}

/*******************
 * Private methods *
 *******************/

void EpocWorker::createCache()
{
    emoEvent = EE_EmoEngineEventCreate();
    emoState = EE_EmoStateCreate();
}

void EpocWorker::clearCache()
{
    EE_EmoStateFree(emoState);
    EE_EmoEngineEventFree(emoEvent);
}
