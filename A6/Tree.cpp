/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: Class that implements an expression tree. Interior nodes
 *  are arithmetic expressions and leaves are constants or variables.
 **/

#include "Tree.h"
using namespace std;

Tree::Tree()
{
}

Tree::Tree(const Tree& left, const Tree& right) :
    left (make_shared<Tree>(left)), right (make_shared<Tree>(right))
{
}

shared_ptr<Tree> Tree::clone() {
    //return make_shared<Tree>(new Tree(left->clone(), right->clone()));
}

shared_ptr<Tree> Tree::getLeftTree() {
    return left;
}

shared_ptr<Tree> Tree::getRightTree() {
    return right;
}