#include "Mood.h"

Mood::Mood() : type(UNKNOWN), power(0), timestamp(0), userTriggered(false) {}
Mood::Mood(Type _type, float _power, int _timestamp, bool _userTriggered) :
    power(_power), timestamp(_timestamp), userTriggered(_userTriggered) {

    if (_type == COUNT) _type = static_cast<Mood::Type>(1);
    type = _type;
}

Mood::Type Mood::getType() const
{
    return type;
}

float Mood::getPower() const
{
    return power;
}

int Mood::getTimestamp() const
{
    return timestamp;
}

bool Mood::getUserTriggered() const
{
    return userTriggered;
}

QString Mood::toString() const
{
    switch (type) {
        case EXCITEMENT: return "excited";
        case ENGAGEMENT: return "engaged";
        case BOREDOM:    return "bored";
        //case MEDITATION:  return "meditating";
        //case FRUSTRATION: return "frustrated";
        default:         return "unknown";
    }
}

