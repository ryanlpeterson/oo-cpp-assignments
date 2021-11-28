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
    array<Floor, NUM_FLOORS> floors {};
    for (int floorNum = 0; floorNum < NUM_FLOORS; floorNum++) {
        floors[floorNum] = Floor(floorNum);
    }

    // init vector to collect done passengers
    vector<Passenger> donePassengers (notYetStartedPassengers.size());

    int curTime = 0;
    while (!notYetStartedPassengers.empty()) {
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
                cout << "===starting passenger" << endl;
                int newPassengerFloorNum = it->getStartFloorNum();
                // add passenger to floor queue
                floors[newPassengerFloorNum].pushPassenger(*it);
                // let elevator's know that someone is at floor
                for (Elevator elevator : elevators) {
                    elevator.setSummonedAtFloor(newPassengerFloorNum, true);
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
        for (Elevator elevator : elevators) {
            if (elevator.isStopped()) {
                // 2a.
                // offload passengers from the elevator
                vector<Passenger> offloadedPassengers = elevator.offloadPassengers();
                // add offloaded passengers to done passengers list
                donePassengers.insert(donePassengers.end(), offloadedPassengers.begin(), offloadedPassengers.end());


                // 2b.
                Floor elevatorCurFloor = floors[elevator.getCurFloorNum()];
                while (elevatorCurFloor.hasWaitingPassengers() && !elevator.isAtCapacity()) {
                    // pop from floor queue
                    Passenger passenger = elevatorCurFloor.popPassenger();
                    // add to elevator
                    elevator.addPassenger(passenger);
                }

                // if floor is now empty, update all elevators' floorsWithWaitingPassengers
                if (!elevatorCurFloor.hasWaitingPassengers()) {
                    for (Elevator elevator : elevators) {
                        elevator.setSummonedAtFloor(elevatorCurFloor.getFloorNum(), false);
                    }
                }
            }
        }


        // 3.
        // for each elevator, update its state
        // i.e. elevator.update()
        for (Elevator elevator : elevators) {
            elevator.update();
        }

        // 4.
        // tick wait time for passengers in floor queues
        for (Floor floor : floors) {
            floor.tickWaitTimeForPassengers();
        }

        // 5.
        // update and display stats
        // pull wait time and travel time from all passengers that have waited or traveled
        //      pull from floor queues, elevator passenger list, and list of done passengers
        //          pulling to get total wait time, total travel time, and number of passengers into the sim so far

        // for now just want to paint a picture of state
        // current sim second
        cout << "curTime: " << curTime << endl;
        // elevators
        cout << "Elevator curFloors: [";
        for (Elevator elevator : elevators) {
            cout << elevator.getCurFloorNum() << ", ";
        }
        cout << "]" << endl;
        // floors
        cout << "Occupied floors: [";
        for (Floor floor : floors) {
            if (floor.hasWaitingPassengers()) {
                cout << floor.getFloorNum() << ":" << floor.getNumWaitingPassengers() << ", ";
            }
        }
        cout << "]" << endl;
        // waiting passengers
        cout << "notYetStartedPassengers.size(): " << notYetStartedPassengers.size() << endl;
        // done passengers
        cout << "donePassengers.size(): " << donePassengers.size() << endl;

        curTime++;
    }


    /*
    std::chrono::seconds interval(1);
    for( int i = 0 ; i < 10 ; ++i ) {
       std::cout << "tick!" << endl;
       //std::this_thread::sleep_for(interval) ;
    }
    */

    return 0;
}