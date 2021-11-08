/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: 
 **/

#include "Divide.h"
#include "Multiply.h"
#include "Add.h"
#include "Subtract.h"
using namespace std;

Divide::Divide(Tree* left, Tree* right) :
    Tree::Tree(left, right)
{
}

Divide::Divide(shared_ptr<Tree> left, shared_ptr<Tree> right) :
    Tree::Tree(left, right)
{
}

double Divide::Evaluate() {
    return getLeftTree()->Evaluate() / getRightTree()->Evaluate();
}

shared_ptr<Tree> Divide::Derivative(string variableName) {
    shared_ptr<Multiply> vdu = make_shared<Multiply>(getRightTree(), getLeftTree()->Derivative(variableName));
    shared_ptr<Multiply> udv = make_shared<Multiply>(getLeftTree(), getRightTree()->Derivative(variableName));
    shared_ptr<Multiply> vv = make_shared<Multiply>(getRightTree(), getRightTree());

    shared_ptr<Subtract> numerator = make_shared<Subtract>(vdu, udv);

    return make_shared<Divide>(numerator, vv);
}

ostream& Divide::formatOutput(ostream& out) const {
    out << "(";
    getLeftTree()->formatOutput(out);
    out << " / ";
    getRightTree()->formatOutput(out);
    out << ")";
    return out;
}