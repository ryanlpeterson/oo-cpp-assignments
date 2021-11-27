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

    vector<Passenger> waitingPassengers;

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
            waitingPassengers.push_back(passenger);
            //cout << "insert passenger " << waitingPassengers.size() << endl;
            
        }
        elevatorFile.close();
    }
    else {
        cout << "Unable to open file";
    }

    sort(waitingPassengers.begin(), waitingPassengers.end());

    cout << "waiting passengers size " << waitingPassengers.size() << endl;

    vector<Passenger>::iterator it = waitingPassengers.begin();
    // Iterate till the end of set
    while (it != waitingPassengers.end()) {
        // Print the element
        cout << (*it).getEndFloorNum() << endl;
        //Increment the iterator
        it++;
    }

    Elevator elevator1 (100);
    array<Elevator, 1> elevators = {elevator1};
    vector<Passenger> donePassengers (waitingPassengers.size());

    int curTime = 0;
    while (!waitingPassengers.empty()) {
        // 1.
        // check waiting passengers to grab any that have a start time that matches curTime
        //      only need to loop into waitingPassengers until passenger.startTime > curTime
        //          then you would know you won't find any more passengers that are ready to be sent to their floors
        // add those matching to their start floor's queue
        // need to update all elevators' floorsWithWaitingPassengers


        // 2.
        // iterate over elevators, for any that are STOPPED:
        // 2a.
        // check the elevators' current floor position and remove any passengers that's dest floor matches the elevators current floor
        // i.e. elevator.offloadPassengers()
        //      elevator will need to update its state information offloadPassengers()
        // offloaded passengers will need add to sim's list of done passengers

        // 2b.
        // check the elevators' current floor position to add the passengers
        //      do until elevator is at capacity or floor is empty
        // i.e. floor.popPassenger() and elevator.addPassenger()
        //      elevator will need to update its state information in addPassenger() (e.g. update its dest floors)
        //      if floor is now empty, update all elevators' floorsWithWaitingPassengers


        // 3.
        // for each elevator, update its state
        // i.e. elevator.update()

        // 4.
        // tick wait time for passengers in floor queues

        // 5.
        // update and display stats
        // pull wait time and travel time from all passengers that have waited or traveled
        //      pull from floor queues, elevator passenger list, and list of done passengers
        //          pulling to get total wait time, total travel time, and number of passengers into the sim so far

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