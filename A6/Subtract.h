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
        // ctor that accepts two raw tree pointers
        Subtract(Tree* left, Tree* right);
        // ctor that accepts two tree shared_ptrs
        Subtract(std::shared_ptr<Tree> p1, std::shared_ptr<Tree> p2);

        // implementations for Tree pure virtual functions
        // subtracts the results of Evaluate called on the two sub-trees
        double Evaluate();
        // subtracts the results of Derivative called on the two sub-trees
        std::shared_ptr<Tree> Derivative(std::string variableName);
        // outputs the subtraction expression to the ostream
        std::ostream& formatOutput(std::ostream& out) const;

    private:
        // uses left and right Trees
};
#endif