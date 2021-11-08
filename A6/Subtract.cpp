/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: Class derived from Tree that implements an subtraction expression.
 **/

#include "Subtract.h"
using namespace std;

// ctor that accepts two raw tree pointers
Subtract::Subtract(Tree* left, Tree* right) :
    Tree(left, right)
{
}

// ctor that accepts two tree shared_ptrs
Subtract::Subtract(shared_ptr<Tree> left, shared_ptr<Tree> right) :
    Tree(left, right)
{
}

// subtracts the results of Evaluate called on the two sub-trees
// left - right
double Subtract::Evaluate() {
    return getLeftTree()->Evaluate() - getRightTree()->Evaluate();
}

// subtracts the results of Derivative called on the two sub-trees
// returns a shared_ptr to the updated expression
// left' - right'
shared_ptr<Tree> Subtract::Derivative(string variableName) {
    return make_shared<Subtract>(getLeftTree()->Derivative(variableName), getRightTree()->Derivative(variableName));
}

// outputs the subtraction expression to the ostream
// returns the updated ostream
// (left.formatOutput() - right.formatOutput())
ostream& Subtract::formatOutput(ostream& out) const {
    out << "(";
    getLeftTree()->formatOutput(out);
    out << " - ";
    getRightTree()->formatOutput(out);
    out << ")";
    return out;
}