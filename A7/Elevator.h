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
        Elevator(int numFloors);

        // Add passenger to the elevator
        void addPassenger(Passenger passenger);

        std::vector<Passenger> offloadPassengers();

        // Update the state and passengers
        void Update();

    private:
    
        // Current floor number
        int currFloorNum;

        std::vector<bool> floorsWithWaitingPassengers;

        // Set of destination floors above current floor
        std::set<int, greater<int> > destFloorsUp;

        // Set of destination floors below current floor
        std::set<int, less<int> > destFloorsDown;

        // Current time in the simulation
        int curTime;

        // Goal time of next floor
        int goalTime;

        // Current elevator state
        State state;

        bool prevDirectionWasUp;

        // Current passengers riding in the elevator
        std::vector<Passenger> passengers;
};
#endif