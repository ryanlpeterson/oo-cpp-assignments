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
    floorsWithWaitingPassengers.resize(numFloors);
    fill(floorsWithWaitingPassengers.begin(), floorsWithWaitingPassengers.end(), false);

    // variables init in header
    // state is STOPPED
    // current time is 0
    // goal time is 0
    // current floor is 0
}

bool Elevator::isStopped() {
    return (state == STOPPED);
}

bool Elevator::isAtCapacity() {
    return (passengers.size() >= MAX_CAPACITY);
}

int Elevator::getCurFloorNum() {
    return curFloorNum;
}

// Constructor with floor number parameter
void Elevator::addPassenger(Passenger passenger)
{
    if (!isAtCapacity())
    {
        // Add passenger to vector of passengers
        passengers.push_back(passenger);

        if (passenger.getEndFloorNum() > curFloorNum)
        {
            destFloorsUp.insert(passenger.getEndFloorNum());
        }
        else
        {
            destFloorsDown.insert(passenger.getEndFloorNum());
        }
    }
}

vector<Passenger> Elevator::offloadPassengers() {
    // need to return and remove passengers that have a dest floor of the current floor
    vector<Passenger> offloadedPassengers;

    // can only offload if stopped
    if (isStopped()) {
        vector<Passenger>::iterator it = passengers.begin();
        // Iterate til the end of set
        while (it != passengers.end()) {
            if (it->getEndFloorNum() == curFloorNum) {
                // add passenger to offload list
                offloadedPassengers.push_back(*it);
                // remove offloaded passenger from passengers list (erase returns iterator at position of element after that erased)
                it = passengers.erase(it);
            }
            else {
                it++;
            }
        }

        // need to remove current floor destFloors
        destFloorsDown.erase(curFloorNum);
        destFloorsUp.erase(curFloorNum);
    }

    return offloadedPassengers;
}

void Elevator::setSummonedAtFloor(int floorNum, bool summon) {
    floorsWithWaitingPassengers[floorNum] = summon;
}

void Elevator::update()
{
    // tick passengers' travel time for certain states
    // 
    // if current time == goal time
    //      move to next state
    //      set new goal time for new state
    //      set current time to 0
    // else
    //      tick current time

    // state transitions
    // STOPPED
    //      goal time: 0
    //      actions: n/a
    //      next state: MOVING_UP, MOVING_DOWN, or stay STOPPED
    //          will need to decide here whether going up or down, need to consider previous state as a tie-break
    //              if both destFloors are empty, look at closest floorsWithWaitingPassengers
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

    // do action no matter if goal time reached
    if (state == MOVING_UP || state == MOVING_DOWN || state == STOPPING) {
        for (Passenger passenger : passengers) {
            passenger.tickTravelTime();
        }
    }

    // if goal time reached, transition state and perform actions for transition
    if (curTime == goalTime) {
        // STOPPED
        if (state == STOPPED) {
            // start moving or stay stopped?
            if (destFloorsUp.size() > 0 && destFloorsDown.size() > 0) {
                // some passengers want to go up, some want to go down, tie-break by continuing previous direction
                if (prevDirectionWasUp) {
                    state = MOVING_UP;
                }
                else {
                    state = MOVING_DOWN;
                }
            }
            // passengers only want to go up
            else if (destFloorsUp.size() > 0) {
                state = MOVING_UP;
            }
            // passengers only want to go down
            else if (destFloorsDown.size() > 0) {
                state = MOVING_DOWN;
            }
            // must be no passengers on board, look at what floors have summoned for elevator
            else {
                int closestUpFloorNum = -1;
                int closestDownFloorNum = -1;
                // find any closest floor above that summoned an elevator
                for (int floorNum = curFloorNum + 1; floorNum < floorsWithWaitingPassengers.size(); floorNum++) {
                    if (floorsWithWaitingPassengers[floorNum]) {
                        closestUpFloorNum = floorNum;
                        break;
                    }
                }
                // find any closest floor below that summoned an elevator
                for (int floorNum = curFloorNum - 1; floorNum >= 0; floorNum--) {
                    if (floorsWithWaitingPassengers[floorNum]) {
                        closestDownFloorNum = floorNum;
                        break;
                    }
                }

                // if both an elevator above and below summoned an elevator, go to the closest
                if (closestUpFloorNum != -1 && closestDownFloorNum != -1) {
                    // get distances to closest floors summoning an elevator
                    int upFloorDist = closestUpFloorNum - curFloorNum;
                    int downFloorDist = curFloorNum - closestDownFloorNum;

                    if (upFloorDist < downFloorDist) {
                        state = MOVING_UP;
                    }
                    else if (upFloorDist > downFloorDist) {
                        state = MOVING_DOWN;
                    }
                    else {
                        //tie-break by continuing previous direction
                        if (prevDirectionWasUp) {
                            state = MOVING_UP;
                        }
                        else {
                            state = MOVING_DOWN;
                        }
                    }
                }
                // only an floor above summoned
                else if (closestUpFloorNum != -1) {
                    state = MOVING_UP;
                }
                // only an floor below summoned
                else if (closestDownFloorNum != -1) {
                    state = MOVING_DOWN;
                }
                // else, no floor is summoning an elevator, state stays STOPPED
            }
        }
        // MOVING_UP
        else if (state == MOVING_UP) {
            curFloorNum++;

            // determine if the floor newly arrived to is a target floor, if so stop
            if (destFloorsUp.find(curFloorNum) != destFloorsUp.end() || floorsWithWaitingPassengers[curFloorNum]) {
                state == STOPPING;
            }
            // else, must not have been a target floor, keep MOVING_UP
        }
        // MOVING_DOWN
        else if (state == MOVING_DOWN) {
            curFloorNum--;

            // determine if the floor newly arrived to is a target floor, if so stop
            if (destFloorsDown.find(curFloorNum) != destFloorsDown.end() || floorsWithWaitingPassengers[curFloorNum]) {
                state == STOPPING;
            }
            // else, must not have been a target floor, keep MOVING_DOWN
        }
        // STOPPING
        else if (state == STOPPING) {
            state = STOPPED;
        }

        // reset current time
        curTime = 0;
        // update goal time based on new state
        if (state == STOPPED) {
            goalTime = 0;
        }
        else if (state == MOVING_UP) {
            goalTime = 10;
            // also remember what will later be previous direction
            prevDirectionWasUp = true;
        }
        else if (state == MOVING_DOWN) {
            goalTime = 10;
            // also remember what will later be previous direction
            prevDirectionWasUp = false;
        }
        else if (state == STOPPING) {
            goalTime = 2;
        }
    }
    else {
        curTime++;
    }
}