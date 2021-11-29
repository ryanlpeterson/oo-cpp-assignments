/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#ifndef PASSENGER_H
#define PASSENGER_H

class Passenger
{
    public:
        // constructor that takes start time, start floor, and end floor
        Passenger(int startTime, int startFloorNum, int endFloorNum);

        // start time getter and setter
        int getStartTime() const;
        void setStartTime(int startTime);

        // start floor getter
        int getStartFloorNum() const;

        // end floor getter
        int getEndFloorNum() const;

        // get wait time
        int getWaitTime() const;
        // tick wait time forward one "second"
        void tickWaitTime();

        // get travel time
        int getTravelTime() const;
        // tick travel time forward one "second"
        void tickTravelTime();

        // comparitor operations to support sorting based on start time
        friend bool operator< (const Passenger& passenger1, const Passenger& passenger2);
        friend bool operator> (const Passenger& passenger1, const Passenger& passenger2);
        friend bool operator<= (const Passenger& passenger1, const Passenger& passenger2);
        friend bool operator>= (const Passenger& passenger1, const Passenger& passenger2);

    private:
        // time in sim that passenger should appear at start floor
        int startTime;

        // start/source floor number
        int startFloorNum;

        // end/dest floor number
        int endFloorNum;
        
        // time spent waiting on floor before moved to elevator
        int elapsedWaitTime;

        // time spent on elevator before reaching end floor
        int elapsedTravelTime;
};

// comparitor operations to support sorting based on start time
inline bool operator< (const Passenger& passenger1, const Passenger& passenger2)
{
    return passenger1.getStartTime() < passenger2.getStartTime();
}

inline bool operator> (const Passenger& passenger1, const Passenger& passenger2)
{
    return passenger1.getStartTime() > passenger2.getStartTime();
}

inline bool operator<= (const Passenger& passenger1, const Passenger& passenger2)
{
    return passenger1.getStartTime() <= passenger2.getStartTime();
}

inline bool operator>= (const Passenger& passenger1, const Passenger& passenger2)
{
    return passenger1.getStartTime() >= passenger2.getStartTime();
}

#endif