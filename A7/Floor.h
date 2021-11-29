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
        // constructor with parameter for floor number
        Floor(int floorNum);

        // floor number getter and setter
        int getFloorNum() const;
        void setFloorNum(int floorNum);

        // add passenger to queue
        void pushPassenger(const Passenger& passenger);

        // return passenger at front of queue and remove from queue
        Passenger popPassenger();

        // return whether there are passengers in the queue
        bool hasWaitingPassengers() const;

        // return a const ref to the queue of passengers
        const std::deque<Passenger>& getPassengers() const;

        // tick wait time forward one "second" for all passengers in queue
        void tickWaitTimeForPassengers();

    private:
        // floor's number
        int floorNum;

        // queue of passengers waiting for the elevator
        std::deque<Passenger> passengers;
};
#endif