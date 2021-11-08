/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 **/

#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "Tree.h"

class Multiply: public Tree
{
    public:
        // ctor that accepts two raw tree pointers
        Multiply(Tree* left, Tree* right);
        // ctor that accepts two tree shared_ptrs
        Multiply(std::shared_ptr<Tree> p1, std::shared_ptr<Tree> p2);

        // implementations for Tree pure virtual functions
        // multiplies the results of Evaluate called on the two sub-trees
        double Evaluate();
        // executes the derivative of the multiplication expression
        std::shared_ptr<Tree> Derivative(std::string variableName);
        // outputs the multiplication expression to the ostream
        std::ostream& formatOutput(std::ostream& out) const;

    private:
        // uses left and right Trees
};
#endif