/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: 
 **/

#include "Constant.h"
using namespace std;

// calls default Tree ctor
Constant::Constant(double value) :
    value (value)
{
}

shared_ptr<Tree> Constant::clone() {
    return make_unique<Tree>(new Constant(value));
}

double Constant::Evaluate() {
    return value;
}

// variableName is unused in this instance
std::shared_ptr<Tree> Constant::Derivative(std::string variableName) {
    return make_unique<Tree>(new Constant(0.0));
}