/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 **/

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <map>

class Tree
{
    public:
        // default ctor
        Tree();
        // ctor that accepts two raw tree pointers
        Tree(Tree* left, Tree* right);
        // ctor that accepts two tree shared_ptrs
        Tree(std::shared_ptr<Tree> p1, std::shared_ptr<Tree> p2);
        // default dtor, virtual because there are other virtual functions
        virtual ~Tree();

        // get sub-trees
        std::shared_ptr<Tree> getLeftTree() const;
        std::shared_ptr<Tree> getRightTree() const;
        
        // pure virtual functions that need implemented by derived classes
        virtual double Evaluate() const = 0;
        virtual std::shared_ptr<Tree> Derivative(std::string variableName) const = 0;
        virtual std::ostream& formatOutput(std::ostream& out) const = 0;

        // static functions to set and get values in the symbol table
        static void setVariableValue(std::string name, double value);
        static double getVariableValue(std::string name);

    private:
        // sub-trees
        std::shared_ptr<Tree> left;
        std::shared_ptr<Tree> right;
        // symbol table that maps variable name to its value
        static std::map<std::string, double> symbolTable;
};

// operator<< for streaming out the tree, non-member because tree needs to be the right operand
std::ostream& operator<<(std::ostream& out, const Tree& tree);

#endif
