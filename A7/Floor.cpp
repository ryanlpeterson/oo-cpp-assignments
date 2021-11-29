/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 * Description: Represents a floor that has a queue of passengers that are waiting
 *  for an elevator. Passengers may be added or removed from the FIFO queue.
 **/

#include "Floor.h"

using namespace std;

// constructor with parameter for floor number
Floor::Floor(int floorNum) :
    floorNum(floorNum)
{
    
}

// floor number getter
int Floor::getFloorNum() const {
    return floorNum;
}

// floor number setter
void Floor::setFloorNum(int newFloorNum) {
    floorNum = newFloorNum;
}

// add passenger to queue
void Floor::pushPassenger(const Passenger& passenger) {
    passengers.push_back(passenger);
}

// return passenger at front of queue and remove from queue
Passenger Floor::popPassenger() {
    // save off copy of passenger that will be returned, as pop will call passenger's destructor
    Passenger nextPassenger = passengers.front();
    // remove passenger from queue
    passengers.pop_front();
    // return
    return nextPassenger;
}

// return whether there are passengers in the queue
bool Floor::hasWaitingPassengers() const {
    return (passengers.size() > 0);
}

// return a const ref to the queue of passengers
const std::deque<Passenger>& Floor::getPassengers() const {
    return passengers;
}

// tick wait time forward one "second" for all passengers in queue
void Floor::tickWaitTimeForPassengers() {
    for (int i = 0; i < passengers.size(); ++i) {
        passengers[i].tickWaitTime();
    }
}