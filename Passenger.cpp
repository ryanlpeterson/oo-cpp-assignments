/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#include "Passenger.h"

// Empty constructor, set member variables to default values
Passenger::Passenger() :
    startFloorNum(-1),
    endFloorNum(-1)
    //status(Passenger::NOT_SET)
{
    
}

// Constructor, set member variables to parameter values
Passenger::Passenger(int startTime, int startFloorNum, int endFloorNum) :
    startTime(startTime),
    startFloorNum(startFloorNum),
    endFloorNum(endFloorNum)
    //status(Passenger::NOT_SET)
{
    
}

// reurn the time the passenger boarded the elevator
int Passenger::getStartTime() {
    return startTime;
}

// return the time the passenger exited the elevator
// int Passenger::getExitTime() {
//     return exitTime;
// }

// Set the time the passenger boarded the elevator
void Passenger::setStartTime(int startTime) {
    startTime = startTime;
}

// Set the time the passenger exited the elevator
// void Passenger::setExitTime(int startTime) {
//     startTime = startTime;
// }

// Return the floor number the passenger started on
int Passenger::getStartFloorNum() {
    return startFloorNum;
}

// Return the floor number the passenger ended on
int Passenger::getEndFloorNum() const {
    return endFloorNum;
}

// Set the status of the passenger and the appropriate time
// void Passenger::setStatus(Passenger::Status newStatus, int time) {
//     status = newStatus;

//     // Invalid status
//     if (status == Passenger::NOT_SET)
//     {
//         return;
//     }

//     // If passenger has boarded elevator and is riding, set start time
//     if (status == Passenger::RIDING)
//     {
//         startTime = time;
//     }

//     // If passenger has gotten off the elevator, set exit time
//     if (status == Passenger::FINISHED)
//     {
//         exitTime = time;
//     }
// }

// Return the status of the passenger
// Passenger::Status Passenger::getStatus() {
//     return status;
// }