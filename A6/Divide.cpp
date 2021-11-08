/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: Class derived from Tree that implements an division expression.
 **/

#include "Divide.h"
#include "Multiply.h"
#include "Add.h"
#include "Subtract.h"
using namespace std;

// ctor that accepts two raw tree pointers
Divide::Divide(Tree* left, Tree* right) :
    Tree(left, right)
{
}

// ctor that accepts two tree shared_ptrs
Divide::Divide(shared_ptr<Tree> left, shared_ptr<Tree> right) :
    Tree(left, right)
{
}

// divides the results of Evaluate called on the two sub-trees
double Divide::Evaluate() const {
    return getLeftTree()->Evaluate() / getRightTree()->Evaluate();
}

// executes the derivative of the division expression
// returns a shared_ptr to the updated expression
// ((right * left') - (left * right')) / (right * right)
shared_ptr<Tree> Divide::Derivative(string variableName) const {
    shared_ptr<Multiply> vdu = make_shared<Multiply>(getRightTree(), getLeftTree()->Derivative(variableName));
    shared_ptr<Multiply> udv = make_shared<Multiply>(getLeftTree(), getRightTree()->Derivative(variableName));
    shared_ptr<Multiply> vv = make_shared<Multiply>(getRightTree(), getRightTree());

    shared_ptr<Subtract> numerator = make_shared<Subtract>(vdu, udv);

    return make_shared<Divide>(numerator, vv);
}

// outputs the division expression to the ostream
// returns the updated ostream
// (left.formatOutput() / right.formatOutput())
ostream& Divide::formatOutput(ostream& out) const {
    out << "(";
    getLeftTree()->formatOutput(out);
    out << " / ";
    getRightTree()->formatOutput(out);
    out << ")";
    return out;
}