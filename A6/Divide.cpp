/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: 
 **/

#include "Divide.h"
using namespace std;

// calls Tree ctor
Divide::Divide(const Tree& left, const Tree& right) :
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

Divide::Divide(std::shared_ptr<Tree> left, std::shared_ptr<Tree> right) :
    Tree::Tree(left, right)
{
}

double Divide::Evaluate() {
    return getLeftTree()->Evaluate() / getRightTree()->Evaluate();
}

// FIXME - update for division
std::shared_ptr<Tree> Divide::Derivative(std::string variableName) {
    // (v*du - u*dv) / v*v
    return make_shared<Divide>(getLeftTree()->Derivative(variableName), getRightTree()->Derivative(variableName));
}