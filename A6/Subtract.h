/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 **/

#ifndef SUBTRACT_H
#define SUBTRACT_H

#include "Tree.h"

class Subtract: public Tree
{
    public:
        Subtract(const Tree& left, const Tree& right);

        Subtract(Tree* left, Tree* right);

        Subtract(std::shared_ptr<Tree> p1, std::shared_ptr<Tree> p2);

        // clone implemented by Tree is good

        double Evaluate();

        std::shared_ptr<Tree> Derivative(std::string variableName);

        std::ostream& formatOutput(std::ostream& out) const;

    private:
        // will use left and right Trees
};
#endif