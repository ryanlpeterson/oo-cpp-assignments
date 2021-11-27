/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#ifndef FLOOR_H
#define FLOOR_H

#include "Passenger.h"
#include <queue>

class Floor
{
    public:

        // Empty constructor
        Floor();

        // Constructor with parameter for floor number
        Floor(int floorNum, std::queue<Passenger> passengers);

        // Return the current floor number
        int getFloorNum();

        // Set the current floor number
        void setFloorNum(int floorNum);

        // begin at the first floor
        static const int startFloor = 1;

    private:
    
        // current floor number
        int floorNum;

        // Queue of passengers waiting for the elevator
        std::queue<Passenger> passengers;
};
#endif