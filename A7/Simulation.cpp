/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#include <iostream>
#include <fstream>
#include "Floor.h"
#include "Passenger.h"
#include "Elevator.h"
#include <chrono>
#include <thread>
#include <sstream>
#include <vector>
#include <array>

using namespace std;

const int NUM_FLOORS = 100;

int main() {

    vector<Passenger> notYetStartedPassengers;

    string line;
    ifstream elevatorFile ("Elevators.csv");

    bool firstLineRead = false;

    int numLines = 0;

    if (elevatorFile.is_open()) {
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

            Passenger passenger(startTime, startFloor, endFloor);
            notYetStartedPassengers.push_back(passenger);
            
        }
        elevatorFile.close();
    }
    else {
        cout << "Unable to open file";
    }

    // sort passengers based on start time for ease later when determining if it is a passenger's start time
    sort(notYetStartedPassengers.begin(), notYetStartedPassengers.end());

    // init elevators
    array<Elevator, 4> elevators = { Elevator(NUM_FLOORS, 10), Elevator(NUM_FLOORS, 10), Elevator(NUM_FLOORS, 10), Elevator(NUM_FLOORS, 10)};

    // init floors
    array<Floor, NUM_FLOORS> floors;
    for (int floorNum = 0; floorNum < NUM_FLOORS; floorNum++) {
        floors[floorNum] = Floor(floorNum);
    }

    int curTime = 0;
    int donePassengersCount = 0;
    int totalNumPassengers = notYetStartedPassengers.size();
    // init vector to collect done passengers
    vector<Passenger> donePassengers;

    while (donePassengersCount < totalNumPassengers) {
        // 1.
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


        // 2.
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


        // 3.
        // for each elevator, update its state
        //      ticks passenger travel times and updates states when appropriate
        for (int i = 0; i < elevators.size(); ++i) {
            elevators[i].update();
        }

        // 4.
        // tick wait time for passengers in floor queues
        for (int i = 0; i < floors.size(); ++i) {
            floors[i].tickWaitTimeForPassengers();
        }

        // 5.
        // display states and stats
        // pull wait time and travel time from all passengers that have waited or traveled
        //      pull from floor queues, elevator passenger list, and list of done passengers
        //          pulling to get total wait time, total travel time, and number of passengers into the sim so far

        // current sim second
        cout << "Current time: " << curTime << endl;

        // output elevator info (<current_floor_num>:<num_passengers>)
        cout << "Elevator curFloors: [";
        for (int i = 0; i < elevators.size(); ++i) {
            cout << elevators[i].getCurFloorNum() << ":" << elevators[i].getNumPassengers() << ", ";
        }
        cout << "]" << endl;

        // output occupied floor info (<floor_num>:<num_passengers>)
        cout << "Occupied floors: [";
        for (int i = 0; i < floors.size(); ++i) {
            if (floors[i].hasWaitingPassengers()) {
                cout << floors[i].getFloorNum() << ":" << floors[i].getNumWaitingPassengers() << ", ";
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
        for (int i = 0; i < floors.size(); ++i) {
            totalWaitTime += floors[i].getTotalPassengerWaitTime();
            numWaitedPassengers += floors[i].getNumWaitingPassengers();
        }
        for (int i = 0; i < elevators.size(); ++i) {
            totalWaitTime += elevators[i].getTotalPassengerWaitTime();
            totalTravelTime += elevators[i].getTotalPassengerTravelTime();
            numWaitedPassengers += elevators[i].getNumPassengers();
            numTraveledPassengers += elevators[i].getNumPassengers();
        }
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

    return 0;
}