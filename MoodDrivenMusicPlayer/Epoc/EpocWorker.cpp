#include <iostream>
#include <map>

#include "Epoc/EpocWorker.h"
#include "GUI/GUI.h"

EpocWorker::EpocWorker(QObject *parent) :
    QObject(parent), userID(0), connected(false), lastMood(UNKNOWN)
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

void EpocWorker::connect()
{
    if(EE_EngineRemoteConnect(EMOCOMPOSER_ADDRESS, EMOCOMPOSER_PORT) == EDK_OK)
    {
        std::cout << "Connected to EmoComposer!" << std::endl;
        connected = true;

        std::cout << "Start receiving mood data!\n" << std::endl;
        createCache();
    }
    else
    {
        std::cout << "Could not connect to EmoComposer! - " << EMOCOMPOSER_ADDRESS << ":" << EMOCOMPOSER_PORT << std::endl;
        connected = false;
    }

    // Notify
    if (connected) emit connectionChanged("Connected to Emotiv Engine. Detect Mood...");
    else           emit connectionChanged("Could not connect to Emotiv Engine");
}

void EpocWorker::addUser()
{
    int eventErrorCode = 0;
    int userErrorCode = 0;
    EE_Event_t eventType;
    bool userAdded = false;

    while (connected && !userAdded)
    {
        eventErrorCode = EE_EngineGetNextEvent(emoEvent);
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

    //while (connected && !kbhit())
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

                // Read expressiv state
                std::map<EE_ExpressivAlgo_t, float> expressivStates;
                EE_ExpressivAlgo_t lowerFaceAction = ES_ExpressivGetLowerFaceAction(emoState);
                float			   lowerFacePower  = ES_ExpressivGetLowerFaceActionPower(emoState);
                expressivStates[lowerFaceAction] = lowerFacePower;

//                std::cout << expressivStates[EXP_SMILE] << std::endl;
//                std::cout << expressivStates[EXP_CLENCH] << std::endl;

                // Set mood
                if (expressivStates[EXP_LAUGH] >= 1.0) mood = HAPPY;
                else if (expressivStates[EXP_SMILE] >= 1.0) mood = RELAXED;
                else if (expressivStates[EXP_CLENCH] >= 1.0) mood = STRESSED;
                else if (expressivStates[EXP_SMIRK_LEFT] >= 1.0 ||
                         expressivStates[EXP_SMIRK_RIGHT] >= 1.0) mood = SAD;
                else mood = UNKNOWN;

                // Call function to handle mood change
                if (mood != lastMood) emit moodChanged(moodString[mood]);
                lastMood = mood;
            }
        }
        else if (eventErrorCode != EDK_NO_EVENT)
        {
            // Error occured -> Stop trying
            emit connectionChanged("Internal error in Emotiv Engine!");
            qDebug() << "Internal error in Emotiv Engine!";
            break;
        }

        // Notify
        //emit connectionChanged("Disconnected to Emotiv Engine");
    }
}

void EpocWorker::disconnect()
{
    if (!connected) return;

    clearCache();
    connected = (EE_EngineDisconnect() == EDK_OK);

    // Notify
    emit connectionChanged("Disconnected to Emotiv Engine");

    qDebug() << "EmoEngine disconnected!";
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
