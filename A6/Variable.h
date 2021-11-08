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
        Variable(std::string name);

        std::shared_ptr<Tree> clone();

        double Evaluate();

        std::shared_ptr<Tree> Derivative(std::string variableName);

        std::ostream& formatOutput(std::ostream& out) const;

        std::string getName() const;

    private:
        std::string name;
        // will NOT use left and right Trees
};
#endif