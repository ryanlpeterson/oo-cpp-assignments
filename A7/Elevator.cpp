/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#include "Elevator.h"

using namespace std;

// Empty constructor, set the start floor to 1
Elevator::Elevator(int numFloors) :
    floorsWithWaitingPassengers (numFloors)
{
    // might have to do floorsWithWaitingPassengers.reserve(numFloors) instead

    // init
    // state is STOPPED
    // current time is 0
    // goal time is 0
    // current floor is 0
}

// Constructor with floor number parameter
void Elevator::addPassenger(Passenger passenger)
{
    if (passengers.size() < 8)
    {
        // Add passenger to vector of passengers
        passengers.push_back(passenger);

        if (passenger.getEndFloorNum() > currFloorNum)
        {
            destFloorsUp.insert(passenger.getEndFloorNum());
        }
        else
        {
            destFloorsDown.insert(passenger.getEndFloorNum());
        }
    }
}

vector<Passenger> offloadPassengers() {
    // need to return and remove passengers that have a dest floor of the current floor

    // need to remove current floor destFloors
}

void Elevator::Update()
{
    // 
    // set<int, greater<int> >::iterator upItr;
    // upItr = destFloorsUp.find(currFloorNum);

    // set<int, greater<int> >::iterator downItr;
    // downItr = destFloorsDown.find(currFloorNum);



    // get current state
    // if current time == goal time
    //      move to next state
    //      set new goal time for new state
    //      set current time to 0
    // else
    //      tick current time

    // states
    // STOPPED
    //      goal time: 0
    //      actions: n/a
    //      next state: MOVING_UP, MOVING_DOWN, or stay STOPPED
    //          will need to decide here whether going up or down, need to consider previous state as a tie-break
    //              if that destFloors is also empty, look at closest floorsWithWaitingPassengers
    //                  if no floorsWithWaitingPassengers are true, just stay STOPPED
    // MOVING_UP / MOVING_DOWN
    //      goal time: 10sec
    //      actions: tick travel time of all passengers onboard
    //      next state: STOPPING, or continue MOVING_UP/MOVING_DOWN
    //          update current floor, as we've reached a new floor
    //          STOPPING if new floor is one of the dest floors, or someone is waiting in the new floor's queue
    //              i.e. check destFloorsUp/destFloorsDown and floorsWithWaitingPassengers
    //          MOVING_UP/MOVING_DOWN, otherwise
    // STOPPING
    //      goal time: 2sec
    //      actions: tick travel time of all passengers onboard
    //      next state: STOPPED
}