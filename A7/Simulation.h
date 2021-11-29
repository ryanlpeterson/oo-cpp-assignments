/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #7: Elevators
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 11/28/21
 **/

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation
{
    public:
        // Constructor with parameter for floor number
        Simulation(int numFloors, int numElevators, int travelTimePerFloor, std::string simFileName);

        void execute();

    private:
        int numFloors;
        int numElevators;
        int travelTimePerFloor;
        std::string simFileName;
};
#endif