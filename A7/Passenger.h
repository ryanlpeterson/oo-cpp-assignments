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

        int getStartTime();

        // int getExitTime();

        void setStartTime(int startTime);

        // void setExitTime(int exitTime);

        // Return the start floor number
        int getStartFloorNum();

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
        // Start floor number
        int startFloorNum;

        // End floor number
        int endFloorNum;

        int startTime;
        
        int elapsedWaitTime;
        int elapsedTravelTime;

        // Current status of the passenger
        //Status status;
};

inline bool operator< (const Passenger& passenger1, const Passenger& passenger2)
{
    return passenger1.getEndFloorNum() < passenger2.getEndFloorNum();
}

inline bool operator> (const Passenger& passenger1, const Passenger& passenger2)
{
    return passenger1.getEndFloorNum() > passenger2.getEndFloorNum();
}

inline bool operator<= (const Passenger& passenger1, const Passenger& passenger2)
{
    return passenger1.getEndFloorNum() <= passenger2.getEndFloorNum();
}

inline bool operator>= (const Passenger& passenger1, const Passenger& passenger2)
{
    return passenger1.getEndFloorNum() >= passenger2.getEndFloorNum();
}

#endif