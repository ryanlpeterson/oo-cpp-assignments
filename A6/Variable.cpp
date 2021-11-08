/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: Class derived from Tree that implements a variable. Corresponding values
 *  can be set via static Tree functions.
 **/

#include "Variable.h"
#include "Constant.h"
using namespace std;

// ctor that accepts the variable name
Variable::Variable(string name) :
    name (name)
{
}

// returns the value set for the variable
// throws out_of_range exception if Tree symbolTable does not have entry for this variable's name
double Variable::Evaluate() {
    return getVariableValue(name);
}

// returns the derivative of the variable w.r.t to the given variable name
// if deriving w.r.t. to this variable, return 1
// otherwise return 0
shared_ptr<Tree> Variable::Derivative(string variableName) {
    if (variableName == name) {
        return make_shared<Constant>(1.0);
    }
    return make_shared<Constant>(0.0);
}

// adds the variable's name to the ostream
// returns the updated ostream
// (name)
ostream& Variable::formatOutput(ostream& out) const {
    out << "(" << getName() << ")";
    return out;
}

// returns the variable's name
string Variable::getName() const {
    return name;
}