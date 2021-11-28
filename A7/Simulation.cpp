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

            //cout << "in while get line " << numLines << endl;

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
            
            //cout << "start time " << startTime << endl;
            //cout << "start floor " << startFloor << endl;
            //cout << "end floor " << endFloor << endl;

            Passenger passenger(startTime, startFloor, endFloor);
            notYetStartedPassengers.push_back(passenger);
            //cout << "insert passenger " << waitingPassengers.size() << endl;
            
        }
        elevatorFile.close();
    }
    else {
        cout << "Unable to open file";
    }

    sort(notYetStartedPassengers.begin(), notYetStartedPassengers.end());

    cout << "waiting passengers size " << notYetStartedPassengers.size() << endl;

    vector<Passenger>::iterator it = notYetStartedPassengers.begin();
    // Iterate til the end of vector
    while (it != notYetStartedPassengers.end()) {
        // Print the element
        cout << "startTime: " << (*it).getStartTime() << ", startFloor: " << (*it).getStartFloorNum() << ", endFloor: " << (*it).getEndFloorNum() << endl;
        //Increment the iterator
        it++;
    }

    // init elevators
    //Elevator elevator1 (NUM_FLOORS);
    //array<Elevator, 1> elevators = { Elevator(NUM_FLOORS) };
    array<Elevator, 4> elevators = { Elevator(NUM_FLOORS), Elevator(NUM_FLOORS), Elevator(NUM_FLOORS), Elevator(NUM_FLOORS)};

    // init floors
    array<Floor, NUM_FLOORS> floors;
    for (int floorNum = 0; floorNum < NUM_FLOORS; floorNum++) {
        floors[floorNum] = Floor(floorNum);
    }

    // init vector to collect done passengers
    vector<Passenger> donePassengers (notYetStartedPassengers.size());

    int curTime = 0;
    int donePassengersCount = 0;
    int totalNumPassengers = notYetStartedPassengers.size();
    bool begin = false;
    while (donePassengersCount < totalNumPassengers) {
        // 1.
        // check waiting passengers to grab any that have a start time that matches curTime
        //      only need to loop into waitingPassengers until passenger.startTime > curTime
        //          then you would know you won't find any more passengers that are ready to be sent to their floors
        // add those matching to their start floor's queue
        // need to update all elevators' floorsWithWaitingPassengers
        vector<Passenger>::iterator it = notYetStartedPassengers.begin();
        // Iterate til the end of set
        while (it != notYetStartedPassengers.end()) {
            if (it->getStartTime() == curTime) {
                cout << "===starting passenger===" << endl;
                begin = true;
                int newPassengerFloorNum = it->getStartFloorNum();
                // add passenger to floor queue
                floors[newPassengerFloorNum].pushPassenger(*it);
                // let elevator's know that someone is at floor
                for (int i = 0; i < elevators.size(); ++i) {
                    elevators[i].setSummonedAtFloor(newPassengerFloorNum, true);
                }
                // remove passenger from waiting passengers list (erase returns iterator at position of element after that erased)
                it = notYetStartedPassengers.erase(it);
            }
            else if (it->getStartTime() > curTime) {
                // since waiting passengers list is sorted, can stop looping now
                break;
            }
            else {
                it++;
            }
        }


        // 2.
        // iterate over elevators, for any that are STOPPED:
        // 2a.
        // check the elevators' current floor position and remove any passengers that's dest floor matches the elevators current floor
        // i.e. elevator.offloadPassengers()
        //      elevator will need to update its state information offloadPassengers()
        // offloaded passengers will need added to sim's list of done passengers

        // 2b.
        // check the elevators' current floor position to add the passengers
        //      do until elevator is at capacity or floor is empty
        // i.e. floor.popPassenger() and elevator.addPassenger()
        //      elevator will need to update its state information in addPassenger() (e.g. update its dest floors)
        //      if floor is now empty, update all elevators' floorsWithWaitingPassengers
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
                Floor elevatorCurFloor = floors[elevators[i].getCurFloorNum()];
                while (elevatorCurFloor.hasWaitingPassengers() && !elevators[i].isAtCapacity()) {
                    // pop from floor queue
                    Passenger passenger = elevatorCurFloor.popPassenger();
                    // add to elevator
                    elevators[i].addPassenger(passenger);
                }

                // if floor is now empty, update all elevators' floorsWithWaitingPassengers
                if (!elevatorCurFloor.hasWaitingPassengers()) {
                    for (int i = 0; i < elevators.size(); ++i) {
                        elevators[i].setSummonedAtFloor(elevatorCurFloor.getFloorNum(), false);
                    }
                }
            }
        }


        // 3.
        // for each elevator, update its state
        // i.e. elevator.update()
        for (int i = 0; i < elevators.size(); ++i) {
            elevators[i].update();
        }

        // 4.
        // tick wait time for passengers in floor queues
        for (int i = 0; i < floors.size(); ++i) {
            floors[i].tickWaitTimeForPassengers();
        }

        // 5.
        // update and display stats
        // pull wait time and travel time from all passengers that have waited or traveled
        //      pull from floor queues, elevator passenger list, and list of done passengers
        //          pulling to get total wait time, total travel time, and number of passengers into the sim so far


        cout << "Average wait time for passengers on each floor: [";
        for (int i = 0; i < floors.size(); ++i) {
            cout << i << ":" << floors[i].getAverageWaitTime() << ", ";
        }
        cout << "]" << endl;

        // for now just want to paint a picture of state
        // current sim second
        cout << "curTime: " << curTime << endl;
        // elevators
        cout << "Elevator curFloors: [";
        for (int i = 0; i < elevators.size(); ++i) {
            cout << elevators[i].getCurFloorNum() << ", ";
        }
        cout << "]" << endl;
        // floors
        cout << "Occupied floors: [";
        for (int i = 0; i < floors.size(); ++i) {
            if (floors[i].hasWaitingPassengers()) {
                cout << floors[i].getFloorNum() << ":" << floors[i].getNumWaitingPassengers() << ", ";
            }
        }
        cout << "]" << endl;
        // waiting passengers
        cout << "notYetStartedPassengers.size(): " << notYetStartedPassengers.size() << endl;
        // done passengers
        cout << "donePassengers.size(): " << donePassengers.size() << endl;

        curTime++;
    }

    return 0;
}