/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#include "Floor.h"

using namespace std;

// Empty constructor, set the start floor to 1
Floor::Floor() :
    floorNum(startFloor)
{
    
}

// Constructor with floor number parameter
Floor::Floor(int floorNum, std::queue<Passenger> passengers) :
    floorNum(floorNum),
    passengers(passengers) 
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