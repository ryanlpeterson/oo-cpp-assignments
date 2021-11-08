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
        Multiply(const Tree& left, const Tree& right);

        Multiply(Tree* left, Tree* right);

        Multiply(std::shared_ptr<Tree> p1, std::shared_ptr<Tree> p2);

        // clone implemented by Tree is good

        double Evaluate();

        std::shared_ptr<Tree> Derivative(std::string variableName);

        std::ostream& formatOutput(std::ostream& out) const;

    private:
        // will use left and right Trees
};
#endif