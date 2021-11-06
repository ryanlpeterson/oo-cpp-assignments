/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: 
 **/

#include "Add.h"
using namespace std;

// calls Tree ctor
Add::Add(const Tree& left, const Tree& right) :
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

Add::Add(std::shared_ptr<Tree> left, std::shared_ptr<Tree> right) :
    Tree::Tree(left, right)
{
}

double Add::Evaluate() {
    return getLeftTree()->Evaluate() + getRightTree()->Evaluate();
}

std::shared_ptr<Tree> Add::Derivative(std::string variableName) {
    return make_shared<Add>(getLeftTree()->Derivative(variableName), getRightTree()->Derivative(variableName));
}