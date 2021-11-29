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
        // constructor with parameters for simulation
        Simulation(int numFloors, int numElevators, int travelTimePerFloor, std::string simFileName);

        // execute simulation
        void execute() const;

    private:
        // instance variables the user sets for the simulation
        int numFloors;
        int numElevators;
        int travelTimePerFloor;
        std::string simFileName;
};
#endif