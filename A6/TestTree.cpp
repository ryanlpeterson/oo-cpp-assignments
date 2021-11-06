/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: This program provides an automated test interface for the Tree cpp file
 **/

#include "Tree.h"
#include "Add.h"
#include "Subtract.h"
#include "Multiply.h"
#include "Divide.h"
#include "Constant.h"
#include "Variable.h"
using namespace std;

int main()
{
    Tree* t = new Add(make_shared<Constant>(1.2), make_shared<Variable>("X"));

    t->setVariableValue("X", 1.0);

    t->setVariableValue("Z", 3.3);

    //make_shared<Tree> dt = t->Derivative("X");

    cout << "Derivative of X " << t->Derivative("X")->Evaluate() << endl;

    cout << "Derivative of Z " <<  t->Derivative("Z")->Evaluate() << endl;

    cout << "Evaluate t (1.2 + 1.0) " << t->Evaluate() << endl;


    Tree* t2 = new Subtract(make_shared<Constant>(7.8), make_shared<Variable>("Y"));

    t2->setVariableValue("Y", 4.2);
    
    cout << "Derivative of Y " << t2->Derivative("Y")->Evaluate() << endl;

    cout << "Evaluate t2 (7.8 - 4.2) " << t2->Evaluate() << endl;


    Tree* t3 = new Multiply(make_shared<Constant>(3.7), make_shared<Variable>("Q"));

    t2->setVariableValue("Q", 9.2);
    
    cout << "Derivative of Q " << t3->Derivative("Q")->Evaluate() << endl;

    cout << "Evaluate t3 (3.7 * (9.2)) " << t3->Evaluate() << endl;

    t = NULL;
    delete t;
}