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

        Tree(const Tree& left, const Tree& right);

        Tree(std::shared_ptr<Tree> p1, std::shared_ptr<Tree> p2);

        virtual ~Tree() {};

        std::shared_ptr<Tree> clone();
        
        virtual double Evaluate();

        virtual std::shared_ptr<Tree> Derivative(std::string variableName);

        // friend allows access to private variables and makes function a non-member
        // access to private variables is necessary for constructing output
        // non-member function is necessary because tree needs to be the right operand
        //friend ostream& operator<<(ostream& out, const Tree& tree);

        std::shared_ptr<Tree> getLeftTree();

        std::shared_ptr<Tree> getRightTree();

        static void setVariableValue(std::string name, double value);

        static double getVariableValue(std::string name);

    private:
        std::shared_ptr<Tree> left;
        std::shared_ptr<Tree> right;

        static std::map<std::string, double> symbolTable;
};
#endif
