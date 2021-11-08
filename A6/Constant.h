/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 **/

#ifndef CONSTANT_H
#define CONSTANT_H

#include "Tree.h"

class Constant : public Tree
{
    public:
        // ctor that accepts a double value
        Constant(double value);

        // implementations for Tree pure virtual functions
        // returns the constant's value
        double Evaluate() const;
        // returns 0
        std::shared_ptr<Tree> Derivative(std::string variableName) const;
        // outputs the constant's value to the ostream
        std::ostream& formatOutput(std::ostream& out) const;

        // returns the constant's value
        double getValue() const;

    private:
        double value;
        // does not use left and right Trees
};
#endif