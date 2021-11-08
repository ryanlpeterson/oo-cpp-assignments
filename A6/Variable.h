/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 **/

#ifndef VARIABLE_H
#define VARIABLE_H

#include "Tree.h"

class Variable : public Tree
{
    public:
        // ctor that accepts the variable name
        Variable(std::string name);

        // implementations for Tree pure virtual functions
        // returns the value set for the variable
        double Evaluate() const;
        // returns the derivative of the variable w.r.t to the given variable name
        std::shared_ptr<Tree> Derivative(std::string variableName) const;
        // outputs the variable's name to the ostream
        std::ostream& formatOutput(std::ostream& out) const;

        // returns the variable's name
        std::string getName() const;

    private:
        std::string name;
        // does not use left and right Trees
};
#endif