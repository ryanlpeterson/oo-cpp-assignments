/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 **/

#ifndef DIVIDE_H
#define DIVIDE_H

#include "Tree.h"

class Divide: public Tree
{
    public:
        // ctor that accepts two raw tree pointers
        Divide(Tree* left, Tree* right);
        // ctor that accepts two tree shared_ptrs
        Divide(std::shared_ptr<Tree> p1, std::shared_ptr<Tree> p2);

        // implementations for Tree pure virtual functions
        // divides the results of Evaluate called on the two sub-trees
        double Evaluate();
        // executes the derivative of the division expression
        std::shared_ptr<Tree> Derivative(std::string variableName);
        // outputs the division expression to the ostream
        std::ostream& formatOutput(std::ostream& out) const;

    private:
        // uses left and right Trees
};
#endif