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

double Constant::Evaluate() {
    return value;
}

// variableName is unused in this instance
shared_ptr<Tree> Constant::Derivative(string variableName) {
    return make_shared<Constant>(0.0);
}

ostream& Constant::formatOutput(ostream& out) const {
    out << "(" << getValue() << ")";
    return out;
}

double Constant::getValue() const {
    return value;
}