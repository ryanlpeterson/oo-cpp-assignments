/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: 
 **/

#include "Add.h"
using namespace std;

Add::Add(Tree* left, Tree* right) :
    Tree::Tree(left, right)
{
}

Add::Add(shared_ptr<Tree> left, shared_ptr<Tree> right) :
    Tree::Tree(left, right)
{
}

double Add::Evaluate() {
    return getLeftTree()->Evaluate() + getRightTree()->Evaluate();
}

shared_ptr<Tree> Add::Derivative(string variableName) {
    return make_shared<Add>(getLeftTree()->Derivative(variableName), getRightTree()->Derivative(variableName));
}

ostream& Add::formatOutput(ostream& out) const {
    out << "(";
    getLeftTree()->formatOutput(out);
    out << " + ";
    getRightTree()->formatOutput(out);
    out << ")";
    return out;
}