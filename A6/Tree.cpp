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

std::map<std::string, double> Tree::symbolTable = map<string, double>();

Tree::Tree()
{
}

Tree::Tree(const Tree& left, const Tree& right) :
    left (make_shared<Tree>(left)), right (make_shared<Tree>(right))
{
}

Tree::Tree(std::shared_ptr<Tree> p1, std::shared_ptr<Tree> p2) :
    left (p1), right(p2)
{
}

shared_ptr<Tree> Tree::clone() {
   return make_shared<Tree>(left->clone(), right->clone());
}

double Tree::Evaluate() {
    return 0.0;
}

std::shared_ptr<Tree> Tree::Derivative(std::string variableName) {
    return clone();
}

shared_ptr<Tree> Tree::getLeftTree() {
    return left;
}

shared_ptr<Tree> Tree::getRightTree() {
    return right;
}

void Tree::setVariableValue(string name, double value) {
    symbolTable[name] = value;
}

double Tree::getVariableValue(string name) {
    return symbolTable.at(name);
}