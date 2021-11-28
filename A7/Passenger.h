/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>

using namespace std;

class Passenger
{
    public:

        // Enumeration of different passenger statuses
        // enum Status
        // {
        //     // Status not set
        //     NOT_SET,
        //     // Waiting to go up
        //     WAITING_UP,
        //     // Waiting to go down
        //     WAITING_DOWN,
        //     // Boarded and riding the elevator
        //     RIDING,
        //     // Finished riding the elevator
        //     FINISHED
        // };

        // Empty constructor
        Passenger();

        // Constructor that takes start and end floor
        Passenger(int startTime, int startFloorNum, int endFloorNum);

        int getStartTime() const;

        void setStartTime(int startTime);

        // Return the start floor number
        int getStartFloorNum() const;

        // Return the end floor number
        int getEndFloorNum() const;

        // Set the passenger's status and update the times
        //void setStatus(Status status, int time);

        //Status getStatus();

        friend bool operator< (const Passenger& passenger1, const Passenger& passenger2);
        friend bool operator> (const Passenger& passenger1, const Passenger& passenger2);

        friend bool operator<= (const Passenger& passenger1, const Passenger& passenger2);
        friend bool operator>= (const Passenger& passenger1, const Passenger& passenger2);

        int getWaitTime();
        void tickWaitTime();
        int getTravelTime();
        void tickTravelTime();

    private:
        int startTime;

        // Start floor number
        int startFloorNum;

        // End floor number
        int endFloorNum;
        
        int elapsedWaitTime = 0;
        int elapsedTravelTime = 0;

        // Current status of the passenger
        //Status status;
};

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