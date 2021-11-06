/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: 
 **/

#include "Multiply.h"
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

Multiply::Multiply(std::shared_ptr<Tree> left, std::shared_ptr<Tree> right) :
    Tree::Tree(left, right)
{
}

double Multiply::Evaluate() {
    return getLeftTree()->Evaluate() * getRightTree()->Evaluate();
}

// FIXME - update for multiplication
std::shared_ptr<Tree> Multiply::Derivative(std::string variableName) {
    // u*dv + v*du
    // so left is u and v is right?
    double udv = getLeftTree()->Evaluate() * getRightTree()->Derivative(variableName)->Evaluate();
    double vdu = getRightTree()->Evaluate() * getLeftTree()->Derivative(variableName)->Evaluate();
    return make_shared<Add>(udv, vdu);
    //return make_shared<Multiply>(getLeftTree()->Derivative(variableName), getRightTree()->Derivative(variableName));
}