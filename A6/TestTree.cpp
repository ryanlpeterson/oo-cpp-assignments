/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: This program provides an automated test interface for the Tree cpp file
 **/

#include "Tree.h"
#include "Add.h"
#include "Constant.h"
#include "Variable.h"
using namespace std;

int main()
{
    Tree* t = new Add(make_shared<Constant>(1.2), make_shared<Variable>("X"));

    t->setVariableValue("X", 1.0);

    cout << t->Evaluate() << endl;

    t = NULL;
    delete t;
}