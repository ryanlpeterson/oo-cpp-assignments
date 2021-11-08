/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: Abstract class that implements an expression tree. Interior nodes
 *  are arithmetic expressions and leaves are constants or variables.
 **/

#include "Tree.h"
using namespace std;

// initialize static symbol table shared between all trees
std::map<std::string, double> Tree::symbolTable = map<string, double>();

// default ctor
Tree::Tree()
{
}

// ctor that accepts two raw tree pointers
Tree::Tree(Tree* left, Tree* right) :
    left(left), right(right)
{
}

// ctor that accepts two tree shared_ptrs
Tree::Tree(shared_ptr<Tree> left, shared_ptr<Tree> right) :
    left (left), right (right)
{
}

// default dtor
Tree::~Tree()
{
}

// returns a shared_ptr to the left tree
shared_ptr<Tree> Tree::getLeftTree() const {
    return left;
}

// returns a shared_ptr to the right tree
shared_ptr<Tree> Tree::getRightTree() const {
    return right;
}

// set value for variable with the given name
// overwrites any existing value set for the variable
void Tree::setVariableValue(string name, double value) {
    symbolTable[name] = value;
}

// returns value set for the variable with the given name
// throws out_of_range exception if no value set for variable
double Tree::getVariableValue(string name) {
    return symbolTable.at(name);
}

// gets the formatted output of the given tree and returns updated ostream
ostream& operator<<(ostream& out, const Tree& tree) {
    return tree.formatOutput(out);
}