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

    cout << "Evaluate t (1.2 + 1.0) " << t->Evaluate() << endl;

    cout << "Derivative of X " << t->Derivative("X")->Evaluate() << endl;

    cout << "Derivative of Z " <<  t->Derivative("Z")->Evaluate() << endl;


    Tree* t2 = new Subtract(make_shared<Constant>(7.8), make_shared<Variable>("Y"));

    t2->setVariableValue("Y", 4.2);

    cout << "Evaluate t2 (7.8 - 4.2) " << t2->Evaluate() << endl;
    
    cout << "Derivative of Y " << t2->Derivative("Y")->Evaluate() << endl;


    /*
    Tree* constant = new Constant(3.7);
    cout << "Evaluate of 3.7 " << constant->Evaluate() << endl;
    shared_ptr<Tree> constant2 = make_shared<Constant>(3.7);
    cout << "Evaluate of 3.7 " << constant2->Evaluate() << endl;
    shared_ptr<Tree> constant3 = constant2->clone();
    cout << "Evaluate of 3.7 " << constant3->Evaluate() << endl;
    */


    Tree* t3 = new Multiply(make_shared<Constant>(3.7), make_shared<Variable>("Q"));

    t3->setVariableValue("Q", 9.2);

    cout << "Evaluate t3 (3.7 * (9.2)) " << t3->Evaluate() << endl;
    
    cout << "Derivative of Q " << t3->Derivative("Q")->Evaluate() << endl;


    Tree* t4 = new Divide(make_shared<Constant>(3.0), make_shared<Variable>("R"));

    t4->setVariableValue("R", 2.0);

    cout << "Evaluate t3 (3.0 / (2.0)) " << t4->Evaluate() << endl;

    cout << "Derivative of R " << t4->Derivative("R")->Evaluate() << endl;



    Tree* t5 = new Add(
        make_shared<Multiply>(make_shared<Constant>(2.3), make_shared<Variable>("X")),
        make_shared<Multiply>(
            make_shared<Variable>("Y"),
            make_shared<Subtract>(make_shared<Variable>("Z"), make_shared<Variable>("X"))));

    t5->setVariableValue("X", 2.0);
    t5->setVariableValue("Y", 3.0);
    t5->setVariableValue("Z", 5.0);

    cout << "variable values " << t5->getVariableValue("X") << ", " << t5->getVariableValue("Y") << ", " << t5->getVariableValue("Z") << endl;

    cout << "Evaluate t5 (assignment desc) " << t5->Evaluate() << endl;

    cout << "Derivative of X " << t5->Derivative("X")->Evaluate() << endl;

    t = NULL;
    delete t;
}