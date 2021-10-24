/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 **/

#include "Tree.h"

class Constant : public Tree
{
    public:
        Constant(double value);

        std::shared_ptr<Tree> clone();

        double Evaluate();

        std::shared_ptr<Tree> Derivative(std::string variableName);

    private:
        double value;
        // will NOT use left and right Trees
};
