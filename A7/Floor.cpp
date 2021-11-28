/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#include "Floor.h"

using namespace std;

// Empty constructor, set the start floor to 1
Floor::Floor()
{
    
}

// Constructor with floor number parameter
Floor::Floor(int floorNum) :
    floorNum(floorNum)
{
    
}

// Return the current floor number
int Floor::getFloorNum() {
    return floorNum;
}

// Set the current floor number
void Floor::setFloorNum(int newFloorNum) {
    floorNum = newFloorNum;
}

void Floor::pushPassenger(const Passenger& passenger) {
    passengers.push_back(passenger);
}

Passenger Floor::popPassenger() {
    // save off copy of passenger that will be returned, as pop will call passenger's destructor
    Passenger nextPassenger = passengers.front();
    // remove passenger from queue
    passengers.pop_front();
    // return
    return nextPassenger;
}

bool Floor::hasWaitingPassengers() {
    return (passengers.size() > 0);
}

int Floor::getNumWaitingPassengers() {
    return passengers.size();
}

void Floor::tickWaitTimeForPassengers() {
    for (Passenger passenger : passengers) {
        passenger.tickWaitTime();
    }
}