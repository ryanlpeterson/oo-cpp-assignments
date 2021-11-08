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
        Constant(double value);

        double Evaluate();

        std::shared_ptr<Tree> Derivative(std::string variableName);

        std::ostream& formatOutput(std::ostream& out) const;

        double getValue() const;

    private:
        double value;
        // will NOT use left and right Trees
};
#endif