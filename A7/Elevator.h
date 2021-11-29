/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Passenger.h"
#include <queue>
#include <iterator>
#include <set>

using namespace std;

class Elevator
{
    public:

        // Enumeration of different elevator states
        enum State
        {
            // Elevator stopped at floor
            STOPPED,
            // Elavator in the process of stopping
            STOPPING,
            // Elevator moving up
            MOVING_UP,
            // Elevator moving down
            MOVING_DOWN
        };

        // Empty constructor
        Elevator(int numFloors, int travelTimePerFloor);

        bool isStopped();

        State getState();

        bool isAtCapacity();

        int getCurFloorNum();

        int getNumPassengers();

        int getTotalPassengerWaitTime();

        int getTotalPassengerTravelTime();

        // Add passenger to the elevator
        void addPassenger(Passenger passenger);

        std::vector<Passenger> offloadPassengers();

        void setSummonedAtFloor(int floorNum, bool summon);

        // Update the state and passengers
        void update();

        void printPassengerInfo();

        void printDestFloorInfo();

    private:

        bool hasFloorToContinueMovingTowards();

        // time it takes to move between floors, default to 10sec
        int travelTimePerFloor = 10;
    
        // Current floor number
        int curFloorNum = 0;

        std::vector<bool> floorsWithWaitingPassengers;

        // Set of destination floors above current floor
        std::set<int, greater<int> > destFloorsUp;

        // Set of destination floors below current floor
        std::set<int, less<int> > destFloorsDown;

        // Current time in the simulation
        int curTime = 0;

        // Goal time of next floor
        int goalTime = 0;

        // Current elevator state
        State state = STOPPED;

        // Previous direction to break ties in deciding which direction to move
        bool prevDirectionWasUp = true;

        // Current passengers riding in the elevator
        std::vector<Passenger> passengers;

        static const int MAX_CAPACITY = 8;
};
#endif