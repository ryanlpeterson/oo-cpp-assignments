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

Tree::Tree(Tree* left, Tree* right) :
    left(left), right(right)
{
}

Tree::Tree(shared_ptr<Tree> left, shared_ptr<Tree> right) :
    left (left), right (right)
{
}

shared_ptr<Tree> Tree::clone() {
   return make_shared<Tree>(left->clone(), right->clone());
}

double Tree::Evaluate() {
    return 0.0;
}

shared_ptr<Tree> Tree::Derivative(string variableName) {
    return clone();
}

shared_ptr<Tree> Tree::getLeftTree() const {
    return left;
}

shared_ptr<Tree> Tree::getRightTree() const {
    return right;
}

ostream& Tree::formatOutput(ostream& out) const {
    out << "...tree...";
    return out;
}

void Tree::setVariableValue(string name, double value) {
    symbolTable[name] = value;
}

double Tree::getVariableValue(string name) {
    return symbolTable.at(name);
}

ostream& operator<<(ostream& out, const Tree& tree) {
    return tree.formatOutput(out);
}