/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 * Description: Represents a passenger that starts on a given floor at a given
 *  simulation time and wants to get to a given destination floor. Keeps track of 
 *  time spend waiting for an elevator and time spent on an elevator traveling to 
 *  the destination.
 **/

#include "Passenger.h"

// constructor that takes start time, start floor, and end floor
Passenger::Passenger(int startTime, int startFloorNum, int endFloorNum) :
    startTime(startTime),
    startFloorNum(startFloorNum),
    endFloorNum(endFloorNum),
    elapsedWaitTime(0),
    elapsedTravelTime(0)
{
    
}

// start time getter
int Passenger::getStartTime() const {
    return startTime;
}

// start time setter
void Passenger::setStartTime(int startTime) {
    startTime = startTime;
}

// start floor getter
int Passenger::getStartFloorNum() const {
    return startFloorNum;
}

// end floor getter
int Passenger::getEndFloorNum() const {
    return endFloorNum;
}

// get wait time
int Passenger::getWaitTime() const {
    return elapsedWaitTime;
}
// tick wait time forward one "second"
void Passenger::tickWaitTime() {
    elapsedWaitTime++;
}

// get travel time
int Passenger::getTravelTime() const {
    return elapsedTravelTime;
}
// tick travel time forward one "second"
void Passenger::tickTravelTime() {
    elapsedTravelTime++;
}