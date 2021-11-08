/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: 
 **/

#include "Multiply.h"
#include "Add.h"
using namespace std;

// calls Tree ctor
Multiply::Multiply(const Tree& left, const Tree& right) :
    Tree::Tree(left, right)
{
}

/*
Add::Add(Tree* p1, Tree* p2)
{
    this->left = make_shared<Tree>(*p1);
    this->right = make_shared<Tree>(*p2);
}
*/

Multiply::Multiply(shared_ptr<Tree> left, shared_ptr<Tree> right) :
    Tree::Tree(left, right)
{
}

double Multiply::Evaluate() {
    return getLeftTree()->Evaluate() * getRightTree()->Evaluate();
}

shared_ptr<Tree> Multiply::Derivative(string variableName) {
    shared_ptr<Multiply> udv = make_shared<Multiply>(getLeftTree(), getRightTree()->Derivative(variableName));
    shared_ptr<Multiply> vdu = make_shared<Multiply>(getRightTree(), getLeftTree()->Derivative(variableName));

    return make_shared<Add>(udv, vdu);
}

ostream& Multiply::formatOutput(ostream& out) const {
    out << "(";
    getLeftTree()->formatOutput(out);
    out << " * ";
    getRightTree()->formatOutput(out);
    out << ")";
    return out;
}