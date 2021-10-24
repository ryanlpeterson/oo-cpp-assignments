/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 **/

#include "Tree.h"

class Add: public Tree
{
    public:
        Add(const Tree& left, const Tree& right);

        // clone implemented by Tree is good

        double Evaluate();

        std::shared_ptr<Tree> Derivative(std::string variableName);

    private:
        // will use left and right Trees
};
