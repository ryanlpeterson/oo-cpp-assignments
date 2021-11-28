/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#ifndef FLOOR_H
#define FLOOR_H

#include "Passenger.h"
#include <deque>

class Floor
{
    public:

        // Empty constructor
        Floor();

        // Constructor with parameter for floor number
        Floor(int floorNum);

        // Return the current floor number
        int getFloorNum();

        // Set the current floor number
        void setFloorNum(int floorNum);

        void pushPassenger(const Passenger& passenger);

        Passenger popPassenger();

        bool hasWaitingPassengers();

        int getNumWaitingPassengers();

        void tickWaitTimeForPassengers();

    private:
    
        // current floor number
        int floorNum;

        // Queue of passengers waiting for the elevator
        std::deque<Passenger> passengers;
};
#endif