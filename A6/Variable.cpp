/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: 
 **/

#include "Variable.h"
#include "Constant.h"
using namespace std;

// calls default Tree ctor
Variable::Variable(string name) :
    name (name)
{
}

double Variable::Evaluate() {
    // potentially throws out_of_range exception if symbolTable does not have entry for this variable's name
    return getVariableValue(name);
}

shared_ptr<Tree> Variable::Derivative(string variableName) {
    if (variableName == name) {
        return make_shared<Constant>(1.0);
    }
    return make_shared<Constant>(0.0);
}

ostream& Variable::formatOutput(ostream& out) const {
    out << "(" << getName() << ")";
    return out;
}

string Variable::getName() const {
    return name;
}