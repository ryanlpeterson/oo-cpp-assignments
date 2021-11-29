/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 * Description: Provides an automated test interface for Simulation.
 **/

#include <string>
#include "Simulation.h"

using namespace std;

int main() {
    int numFloors = 100;
    int numElevators = 4;
    int travelTimePerFloor = 5;
    string simFileName ("Elevators.csv");

    Simulation sim(numFloors, numElevators, travelTimePerFloor, simFileName);

    sim.execute();

    return 0;
}