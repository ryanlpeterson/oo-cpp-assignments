/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: 
 **/

#include "Subtract.h"
using namespace std;

Subtract::Subtract(Tree* left, Tree* right) :
    Tree::Tree(left, right)
{
}

Subtract::Subtract(shared_ptr<Tree> left, shared_ptr<Tree> right) :
    Tree::Tree(left, right)
{
}

double Subtract::Evaluate() {
    return getLeftTree()->Evaluate() - getRightTree()->Evaluate();
}

shared_ptr<Tree> Subtract::Derivative(string variableName) {
    return make_shared<Subtract>(getLeftTree()->Derivative(variableName), getRightTree()->Derivative(variableName));
}

ostream& Subtract::formatOutput(ostream& out) const {
    out << "(";
    getLeftTree()->formatOutput(out);
    out << " - ";
    getRightTree()->formatOutput(out);
    out << ")";
    return out;
}