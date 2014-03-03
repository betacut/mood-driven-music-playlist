#ifndef MOOD_H
#define MOOD_H

#include <QString>

class Mood
{
public:
    enum Type
    {
        UNKNOWN = 0,
        EXCITEMENT, // titillation, nervousness, agitation
        ENGAGEMENT, // alertness, vigilance, concentration, stimulation, interest
        BOREDOM,    // bored
        //MEDITATION, // Relaxed
        //FRUSTRATION // Stressed

        COUNT
    };
// Constructor
    Mood();
    Mood(Type, float, int, bool);
// Getter
    Type getType() const;
    float getPower() const;
    int getTimestamp() const;
    bool getUserTriggered() const;
    QString toString() const;
// Operator
    inline bool operator==(const Mood& mood) { return (this->type == mood.getType()); }
    inline bool operator!=(const Mood& mood) { return (this->type != mood.getType()); }
    inline bool operator==(const Type& type) { return (this->type == type); }
    inline bool operator!=(const Type& type) { return (this->type != type); }
    inline operator int() {return type;}

private:
    Type type;
    float power;
    int timestamp;
    bool userTriggered;
};

#endif // MOOD_H
