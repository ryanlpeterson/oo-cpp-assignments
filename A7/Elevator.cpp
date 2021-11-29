/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 * Description: Represents an elevator containing a list of passengers. Transitions
 *  between states of STOPPED, MOVING_UP, MOVING_DOWN, and STOPPING. Passengers
 *  may be added or removed from the elevator. The elevator can only hold a MAX_CAPACITY
 *  number of passengers. Passengers on floors may request an elevator. Elevators will
 *  stop for any floor that is a destination floor of a passenger or where passengers are
 *  waiting on the floor for an elevator.
 **/

#include "Elevator.h"

using namespace std;

// constructor that takes the number of floors and the time it takes to travel one floor
Elevator::Elevator(int numFloors, int travelTimePerFloor) :
    floorsWithWaitingPassengers (numFloors),
    travelTimePerFloor (travelTimePerFloor)
{
    floorsWithWaitingPassengers.resize(numFloors);
    fill(floorsWithWaitingPassengers.begin(), floorsWithWaitingPassengers.end(), false);

    // variables init in header
    // state is STOPPED
    // current time is 0
    // goal time is 0
    // current floor is 0
}

// returns whether the elevator is currently in the STOPPED state
bool Elevator::isStopped() const {
    return (state == STOPPED);
}

// returns whether the number of passengers onboard is equal to the MAX_CAPACITY
bool Elevator::isAtCapacity() const {
    return (passengers.size() >= MAX_CAPACITY);
}

// current floor number getter
int Elevator::getCurFloorNum() const {
    return curFloorNum;
}

// return a const ref to the list of passengers
const std::vector<Passenger>& Elevator::getPassengers() const {
    return passengers;
}

// add passenger to the elevator
void Elevator::addPassenger(Passenger passenger)
{
    if (!isAtCapacity())
    {
        // add passenger to vector of passengers
        passengers.push_back(passenger);

        // update sets for dest floors of passengers onboard
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

// remove passengers whose end floor matches the current floor
vector<Passenger> Elevator::offloadPassengers() {
    // need to return and remove passengers that have a dest floor of the current floor
    vector<Passenger> offloadedPassengers;

    // can only offload if stopped
    if (isStopped()) {
        vector<Passenger>::iterator it = passengers.begin();
        // iterate til the end of set
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

        // need to remove current floor from destFloors
        destFloorsDown.erase(curFloorNum);
        destFloorsUp.erase(curFloorNum);
    }

    // return passengers offloaded
    return offloadedPassengers;
}

// indicates to the elevator whether a passenger wants an elevator at a given floor
void Elevator::setSummonedAtFloor(int floorNum, bool summon) {
    floorsWithWaitingPassengers[floorNum] = summon;
}

// update the state of the elevator for one sim "second"
void Elevator::update()
{
    // tick passengers' travel time if moving or stopping
    
    // if current time == goal time
    //      move to next state
    //      set new goal time for new state
    //      set current time to 0
    // else
    //      tick time progress towards goal time

    // Summary of state transitions:
    // STOPPED
    //      goal time: 0
    //      next state: MOVING_UP, MOVING_DOWN, or stay STOPPED
    //          will need to decide here whether going up or down, need to consider previous state as a tie-break
    //              if both destFloors are empty, look at closest floorsWithWaitingPassengers
    //                  if no floorsWithWaitingPassengers are true, just stay STOPPED
    // MOVING_UP / MOVING_DOWN
    //      goal time: <travelTimePerFloor>sec
    //      next state: STOPPING, or continue MOVING_UP/MOVING_DOWN
    //          update current floor, as we've reached a new floor
    //          STOPPING if new floor is one of the dest floors, or someone is waiting in the new floor's queue
    //              i.e. check destFloorsUp/destFloorsDown and floorsWithWaitingPassengers
    //          MOVING_UP/MOVING_DOWN, otherwise
    // STOPPING
    //      goal time: 2sec
    //      next state: STOPPED

    // ticket travel time for each passenger on board, unless might be offloaded
    if (state == MOVING_UP || state == MOVING_DOWN || state == STOPPING) {
        for (int i = 0; i < passengers.size(); i++) {
            passengers[i].tickTravelTime();
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

                    // move towards closest floor summoning an elevator
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
                // only a floor above summoned
                else if (closestUpFloorNum != -1) {
                    state = MOVING_UP;
                }
                // only a floor below summoned
                else if (closestDownFloorNum != -1) {
                    state = MOVING_DOWN;
                }
                // else, no floor is summoning an elevator, state stays STOPPED
            }
        }
        // MOVING_UP
        else if (state == MOVING_UP) {
            // update current floor number
            curFloorNum++;

            // determine if the floor newly arrived to is a target floor, if so stop
            // also stop if there is no longer a floor to move towards (likely another elevator arrived to a summoning floor first)
            if (destFloorsUp.find(curFloorNum) != destFloorsUp.end() || floorsWithWaitingPassengers[curFloorNum] || !hasFloorToContinueMovingTowards()) {
                state = STOPPING;
            }
            // else, must not have been a target floor, keep MOVING_UP
        }
        // MOVING_DOWN
        else if (state == MOVING_DOWN) {
            // update current floor number
            curFloorNum--;

            // determine if the floor newly arrived to is a target floor, if so stop
            // also stop if there is no longer a floor to move towards (likely another elevator arrived to a summoning floor first)
            if (destFloorsDown.find(curFloorNum) != destFloorsDown.end() || floorsWithWaitingPassengers[curFloorNum] || !hasFloorToContinueMovingTowards()) {
                state = STOPPING;
            }
            // else, must not have been a target floor, keep MOVING_DOWN
        }
        // STOPPING
        else if (state == STOPPING) {
            // simply stop
            state = STOPPED;
        }

        // reset current time
        curTime = 0;
        // update goal time based on new state
        if (state == STOPPED) {
            goalTime = 0;
        }
        else if (state == MOVING_UP) {
            goalTime = travelTimePerFloor;
            // also remember what will later be previous direction for potential tie-breaks
            prevDirectionWasUp = true;
        }
        else if (state == MOVING_DOWN) {
            goalTime = travelTimePerFloor;
            // also remember what will later be previous direction for potential tie-breaks
            prevDirectionWasUp = false;
        }
        else if (state == STOPPING) {
            goalTime = 2;
        }
    }
    else {
        // tick time towards goal time
        curTime++;
    }
}

// returns whether there is still a valid target floor in the direction currently being moved
bool Elevator::hasFloorToContinueMovingTowards() const {
    if (state == MOVING_UP) {
        // check if there are any dest floors set above (i.e. there is a passenger)
        if (destFloorsUp.size() > 0) {
            return true;
        }

        // if no dest floors are set, check if any floors above are summoning an elevator
        bool isAtLeastOneFloorWithWaitingPassenger = false;
        for (int i = curFloorNum + 1; i < floorsWithWaitingPassengers.size(); i++) {
            if (floorsWithWaitingPassengers[i]) {
                isAtLeastOneFloorWithWaitingPassenger = true;
                break;
            }
        }
        return isAtLeastOneFloorWithWaitingPassenger;
    }
    else if (state == MOVING_DOWN) {
        // check if there are any dest floors set below (i.e. there is a passenger)
        if (destFloorsDown.size() > 0) {
            return true;
        }

        // if no dest floors are set, check if any floors below are summoning an elevator
        bool isAtLeastOneFloorWithWaitingPassenger = false;
        for (int i = curFloorNum - 1; i >= 0; i--) {
            if (floorsWithWaitingPassengers[i]) {
                isAtLeastOneFloorWithWaitingPassenger = true;
                break;
            }
        }
        return isAtLeastOneFloorWithWaitingPassenger;
    }
    return false;
}