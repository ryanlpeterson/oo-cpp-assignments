/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 * Description: Executes an elevator simulation based on the given number of floors,
 *  number of elevators, time it takes an elevator to travel a floor, and a file with
 *  passenger information. Simulations update state transition information every second,
 *  and outputs state and statistic info.
 **/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <deque>
#include <vector>
#include "Floor.h"
#include "Passenger.h"
#include "Elevator.h"
#include "Simulation.h"

using namespace std;

// Constructor with parameters for simulation
Simulation::Simulation(int numFloors, int numElevators, int travelTimePerFloor, string simFileName) :
    numFloors (numFloors),
    numElevators (numElevators),
    travelTimePerFloor (travelTimePerFloor),
    simFileName (simFileName)
{

}

// executes the simulation
// reads the simulation file to construct passenger information
// outputs state and statistic information to cout each simulation second
void Simulation::execute() const {
    // list to store passengers constructed from the sim file
    vector<Passenger> notYetStartedPassengers;

    // read the sim file and construct passengers
    string line;
    ifstream elevatorFile (simFileName);
    int numLines = 0;

    if (elevatorFile.is_open()) {
        // loop while lines remain in the file
        while (getline (elevatorFile, line)) {
            numLines++;

            // Skip header line
            if (numLines == 1) {
                continue;
            }

            stringstream stringStream(line);
            int startTime;
            int startFloor;
            int endFloor;
            int numIterations = 0;

            // pull passenger info from the line
            while (stringStream.good()) {
                string substr;
                getline(stringStream, substr, ',');

                if (numIterations == 0) {
                    startTime = stoi(substr);
                }
                else if (numIterations == 1) {
                    startFloor = stoi(substr);
                }
                else if (numIterations == 2) {
                    endFloor = stoi(substr);
                }

                if (numIterations < 3) {
                    numIterations++;
                }
                else {
                    numIterations = 0;
                }
            }

            // construct the passenger and add them to the notYetStartedPassengers list
            Passenger passenger(startTime, startFloor, endFloor);
            notYetStartedPassengers.push_back(passenger);
        }
        // close the file
        elevatorFile.close();
    }
    else {
        cout << "Unable to open file";
        return;
    }

    // sort passengers based on start time for ease later when determining if it is a passenger's start time
    sort(notYetStartedPassengers.begin(), notYetStartedPassengers.end());

    // init elevators for this sim execution
    vector<Elevator> elevators;
    for (int i = 0; i < numElevators; i++) {
        //elevators[i] = Elevator(numFloors, travelTimePerFloor);
        elevators.push_back(Elevator(numFloors, travelTimePerFloor));
    }

    // init floors for this sim execution
    vector<Floor> floors;
    for (int floorNum = 0; floorNum < numFloors; floorNum++) {
        floors.push_back(Floor(floorNum));
    }

    // init vector to collect done passengers
    vector<Passenger> donePassengers;
    int donePassengersCount = 0;

    // run the simulation, where each loop is one "second" in the sim
    int curTime = 0;
    int totalNumPassengers = notYetStartedPassengers.size();
    while (donePassengersCount < totalNumPassengers) {
        // 1. Put any passengers that start this second onto their respective floor
        // check waiting passengers to grab any that have a start time that matches curTime
        //      only need to loop into waitingPassengers until passenger.startTime > curTime
        //          then you would know you won't find any more passengers that are ready to be sent to their floors (since list is sorted)
        // add those matching to their start floor's queue
        // need to update all elevators' floorsWithWaitingPassengers
        vector<Passenger>::iterator it = notYetStartedPassengers.begin();
        while (it != notYetStartedPassengers.end()) {
            if (it->getStartTime() == curTime) {
                // found passenger that should start now
                int newPassengerFloorNum = it->getStartFloorNum();
                if (newPassengerFloorNum == it->getEndFloorNum()) {
                    // passenger is already at target floor, just move right to done
                    donePassengers.push_back(*it);
                    donePassengersCount++;
                }
                else {
                    // add passenger to floor queue
                    floors[newPassengerFloorNum].pushPassenger(*it);
                    // let all elevators know that someone is at floor
                    for (int i = 0; i < elevators.size(); ++i) {
                        elevators[i].setSummonedAtFloor(newPassengerFloorNum, true);
                    }
                }
                // remove passenger from waiting passengers list (erase returns iterator at position of element after that erased)
                it = notYetStartedPassengers.erase(it);
            }
            else if (it->getStartTime() > curTime) {
                // since waiting passengers list is sorted, can stop looping now
                break;
            }
            else {
                // move iterator to next passenger
                it++;
            }
        }


        // 2. Move passengers off and onto elevators
        // iterate over elevators, for any that are STOPPED:
        
        // 2a.
        // check the elevators' current floor position and offload any passengers that's dest floor matches the elevators current floor
        //      i.e. elevator.offloadPassengers()
        // offloaded passengers are added to sim's list of done passengers

        // 2b.
        // check the elevators' current floor position to add the passengers
        //      do until elevator is at capacity or floor is empty
        // i.e. floor.popPassenger() and elevator.addPassenger()
        //      if floor is now empty, update all elevators' floorsWithWaitingPassengers (no one needs picked up there anymore)
        for (int i = 0; i < elevators.size(); ++i) {
            if (elevators[i].isStopped()) {
                // 2a.
                // offload passengers from the elevator
                vector<Passenger> offloadedPassengers = elevators[i].offloadPassengers();
                // add offloaded passengers to done passengers list
                if (offloadedPassengers.size() > 0) {
                    donePassengers.insert(donePassengers.end(), offloadedPassengers.begin(), offloadedPassengers.end());
                    donePassengersCount+= offloadedPassengers.size();
                }

                // 2b.
                Floor& elevatorCurFloor = floors[elevators[i].getCurFloorNum()];
                // add any passengers at the floor onto the elevator until elevator is full
                while (elevatorCurFloor.hasWaitingPassengers() && !elevators[i].isAtCapacity()) {
                    // pop from floor queue
                    Passenger passenger = elevatorCurFloor.popPassenger();
                    // add to elevator
                    elevators[i].addPassenger(passenger);
                }

                // if floor is now empty, update all elevators' floorsWithWaitingPassengers (no one needs picked up there anymore)
                if (!elevatorCurFloor.hasWaitingPassengers()) {
                    for (int i = 0; i < elevators.size(); ++i) {
                        elevators[i].setSummonedAtFloor(elevatorCurFloor.getFloorNum(), false);
                    }
                }
            }
        }


        // 3. For each elevator, update
        // tick passenger travel times and update states when appropriate
        for (int i = 0; i < elevators.size(); ++i) {
            elevators[i].update();
        }

        // 4. For each floor, update
        // tick wait time for passengers in floor queues
        for (int i = 0; i < floors.size(); ++i) {
            floors[i].tickWaitTimeForPassengers();
        }

        // 5. Display states and stats
        // pull wait time and travel time from all passengers that have waited or traveled
        //      pull from floor queues, elevator passenger list, and list of done passengers
        //          pulling to get total wait time, total travel time, and number of passengers into the sim so far

        // current sim second
        cout << "Current time: " << curTime << endl;

        // output elevator info (<current_floor_num>:<num_passengers>)
        cout << "Elevator curFloors: [";
        for (int i = 0; i < elevators.size(); ++i) {
            cout << elevators[i].getCurFloorNum() << ":" << elevators[i].getPassengers().size() << ", ";
        }
        cout << "]" << endl;

        // output occupied floor info (<floor_num>:<num_passengers>)
        cout << "Occupied floors: [";
        for (int i = 0; i < floors.size(); ++i) {
            if (floors[i].hasWaitingPassengers()) {
                cout << floors[i].getFloorNum() << ":" << floors[i].getPassengers().size() << ", ";
            }
        }
        cout << "]" << endl;

        // output number of done passengers
        cout << "donePassengersCount: " << donePassengersCount << endl;

        // statistics
        // collect total wait and travel times
        int totalWaitTime = 0;
        int numWaitedPassengers = 0;
        int totalTravelTime = 0;
        int numTraveledPassengers = 0;
        // get times and counts from floors
        for (int i = 0; i < floors.size(); ++i) {
            const deque<Passenger>& floorsPassengers = floors[i].getPassengers();
            for (int j = 0; j < floorsPassengers.size(); j++) {
                totalWaitTime += floorsPassengers[j].getWaitTime();
            }
            numWaitedPassengers += floorsPassengers.size();
        }
        // get times and counts from elevators
        for (int i = 0; i < elevators.size(); ++i) {
            const vector<Passenger>& elevatorsPassengers = elevators[i].getPassengers();
            for (int j = 0; j < elevatorsPassengers.size(); j++) {
                totalWaitTime += elevatorsPassengers[j].getWaitTime();
                totalTravelTime += elevatorsPassengers[j].getTravelTime();
            }
            numWaitedPassengers += elevatorsPassengers.size();
            numTraveledPassengers += elevatorsPassengers.size();
        }
        // get times and counts from done passengers list
        for (int i = 0; i < donePassengersCount; i++) {
            totalWaitTime += donePassengers[i].getWaitTime();
            totalTravelTime += donePassengers[i].getTravelTime();
        }
        numWaitedPassengers += donePassengersCount;
        numTraveledPassengers += donePassengersCount;

        // calculate and print average wait time
        double averageWaitTime = 0;
        if (numWaitedPassengers > 0) {
            averageWaitTime = ((double)totalWaitTime / numWaitedPassengers);
        }
        cout << "Average wait time: " << averageWaitTime << endl;
        // calculate and print average travel time
        double averageTravelTime = 0;
        if (numTraveledPassengers > 0) {
            averageTravelTime = ((double)totalTravelTime / numTraveledPassengers);
        }
        cout << "Average travel time: " << averageTravelTime << endl;

        cout << endl;

        curTime++;
    }
    // while loop exited, all passengers must be in done list, sim complete
    cout << "Simulation complete." << endl;
}