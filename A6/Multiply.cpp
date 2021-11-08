/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: Class derived from Tree that implements an multiplication expression.
 **/

#include "Multiply.h"
#include "Add.h"
using namespace std;

// ctor that accepts two raw tree pointers
Multiply::Multiply(Tree* left, Tree* right) :
    Tree(left, right)
{
}

// ctor that accepts two tree shared_ptrs
Multiply::Multiply(shared_ptr<Tree> left, shared_ptr<Tree> right) :
    Tree(left, right)
{
}

// multiplies the results of Evaluate called on the two sub-trees
// left * right
double Multiply::Evaluate() {
    return getLeftTree()->Evaluate() * getRightTree()->Evaluate();
}

// executes the derivative of the multiplication expression
// returns a shared_ptr to the updated expression
// (left * right') + (right * left')
shared_ptr<Tree> Multiply::Derivative(string variableName) {
    shared_ptr<Multiply> udv = make_shared<Multiply>(getLeftTree(), getRightTree()->Derivative(variableName));
    shared_ptr<Multiply> vdu = make_shared<Multiply>(getRightTree(), getLeftTree()->Derivative(variableName));

    return make_shared<Add>(udv, vdu);
}

// outputs the multiplication expression to the ostream
// returns the updated ostream
// (left.formatOutput() * right.formatOutput())
ostream& Multiply::formatOutput(ostream& out) const {
    out << "(";
    getLeftTree()->formatOutput(out);
    out << " * ";
    getRightTree()->formatOutput(out);
    out << ")";
    return out;
}