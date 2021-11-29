/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Passenger.h"
#include <set>
#include <vector>

class Elevator
{
    public:

        // enumerator of different elevator states
        enum ElevatorState
        {
            // elevator is stopped at floor
            STOPPED,
            // elavator is in the process of stopping
            STOPPING,
            // elevator is moving up
            MOVING_UP,
            // elevator is moving down
            MOVING_DOWN
        };

        // constructor that takes the number of floors and the time it takes to travel one floor
        Elevator(int numFloors, int travelTimePerFloor);

        // returns whether the elevator is currently in the STOPPED state
        bool isStopped() const;

        // returns whether the number of passengers onboard is equal to the MAX_CAPACITY
        bool isAtCapacity() const;

        // current floor number getter
        int getCurFloorNum() const;

        // return a const ref to the list of passengers
        const std::vector<Passenger>& getPassengers() const;

        // add passenger to the elevator
        void addPassenger(Passenger passenger);

        // remove passengers whose end floor matches the current floor
        std::vector<Passenger> offloadPassengers();

        // indicates to the elevator whether a passenger wants an elevator at a given floor
        void setSummonedAtFloor(int floorNum, bool summon);

        // update the state of the elevator for one sim "second"
        void update();

    private:
        // returns whether there is still a valid target floor in the direction currently being moved
        bool hasFloorToContinueMovingTowards() const;

        // time it takes to move between floors
        int travelTimePerFloor;
    
        // current floor number
        int curFloorNum = 0;

        // boolean list for floors, true indicates a passenger is waiting for pickup at the floor corresponding to the index
        std::vector<bool> floorsWithWaitingPassengers;

        // set of destination floors above current floor
        std::set<int, std::greater<int> > destFloorsUp;

        // set of destination floors below current floor
        std::set<int, std::less<int> > destFloorsDown;

        // current time elapsed since last goal time reached
        int curTime = 0;

        // goal time until state may change
        int goalTime = 0;

        // current elevator state
        ElevatorState state = STOPPED;

        // previous direction to break ties in deciding which direction to move
        bool prevDirectionWasUp = true;

        // current passengers riding in the elevator
        std::vector<Passenger> passengers;

        // max number of passengers that may be on the elevator at a given time
        static const int MAX_CAPACITY = 8;
};
#endif