/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: Class derived from Tree that implements a numeric constant.
 **/

#include "Constant.h"
using namespace std;

// ctor that accepts a double value
Constant::Constant(double value) :
    value (value)
{
}

// returns the constant's value
double Constant::Evaluate() const {
    return value;
}

// returns 0
// variableName is unused in this instance
shared_ptr<Tree> Constant::Derivative(string variableName) const {
    return make_shared<Constant>(0.0);
}

// outputs the constant's value to the ostream
// returns the udpated ostream
// (value)
ostream& Constant::formatOutput(ostream& out) const {
    out << "(" << getValue() << ")";
    return out;
}

// returns the constant's value
double Constant::getValue() const {
    return value;
}