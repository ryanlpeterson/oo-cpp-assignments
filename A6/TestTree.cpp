/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #6: Expression Tree
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/31/2021
 * Description: This program provides an automated test interface for the Tree cpp file.
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
    // 1. Addition simple case
    // 1.2 + X
    Tree* t = new Add(new Constant(1.2), new Variable("X"));
    t->setVariableValue("X", 1.0);

    cout << "1." << endl;
    cout << "Expression: " <<  *t << endl;
    cout << "X = " << t->getVariableValue("X") << endl;

    // should evaluate to: 2.2
    cout << "Evaluated: " << t->Evaluate() << endl;
    // 0 + 1
    cout << "Derivative w.r.t. X: " << *(t->Derivative("X")) << endl;
    // derivative should evaluate to: 1
    cout << "Derivative Evaluated: " << t->Derivative("X")->Evaluate() << endl;

    cout << endl;
    delete t;
    


    // 2. Subtraction simple case
    // 7.8 - Y
    t = new Subtract(new Constant(7.8), new Variable("Y"));
    t->setVariableValue("Y", 4.2);

    cout << "2." << endl;
    cout << "Expression: " << *t << endl;
    cout << "Y = " << t->getVariableValue("Y") << endl;

    // should evaluate to: 3.6
    cout << "Evaluated: " << t->Evaluate() << endl;
    // 0 - 1
    cout << "Derivative w.r.t. Y: " << *(t->Derivative("Y")) << endl;
    // derivative should evaluate to: -1
    cout << "Derivative Evaluated: " << t->Derivative("Y")->Evaluate() << endl;

    cout << endl;
    delete t;



    // 3. Multiplication simple case
    // 3.7 * Z
    t = new Multiply(new Constant(3.7), new Variable("Z"));
    t->setVariableValue("Z", 9.2);

    cout << "3." << endl;
    cout << "Expression: " << *t << endl;
    cout << "Z = " << t->getVariableValue("Z") << endl;

    // should evaluate to: 34.04
    cout << "Evaluated: " << t->Evaluate() << endl;
    // (3.7 * 1) + (Z * 0)
    cout << "Derivative w.r.t. Z: " << *(t->Derivative("Z")) << endl;
    // derivative should evaluate to: 3.7
    cout << "Derivative Evaluated: " << t->Derivative("Z")->Evaluate() << endl;

    cout << endl;
    delete t;



    // 4. Dividision simple case
    // 3.0 / W
    t = new Divide(new Constant(3.0), new Variable("W"));
    t->setVariableValue("W", 2.0);

    cout << "4." << endl;
    cout << "Expression: " << *t << endl;
    cout << "W = " << t->getVariableValue("W") << endl;

    // should evaluate to: 1.5
    cout << "Evaluated: " << t->Evaluate() << endl;
    // ((W * 0) - (3 * 1)) / (W * W)
    cout << "Derivative w.r.t. W: " << *(t->Derivative("W")) << endl;
    // derivative should evaluate to: -0.75
    cout << "Derivative Evaluated: " << t->Derivative("W")->Evaluate() << endl;

    cout << endl;
    delete t;



    // 5. Complex case
    // (2.3 * X) + (Y * (Z - X))
    t = new Add(
        new Multiply(new Constant(2.3), new Variable("X")),
        new Multiply(
            new Variable("Y"),
            new Subtract(new Variable("Z"), new Variable("X"))));
    t->setVariableValue("X", 2.0);
    t->setVariableValue("Y", 3.0);
    t->setVariableValue("Z", 5.0);

    cout << "5." << endl;
    cout << "Expression: " << *t << endl;
    cout << "X = " << t->getVariableValue("X") << endl;
    cout << "Y = " << t->getVariableValue("Y") << endl;
    cout << "Z = " << t->getVariableValue("Z") << endl;

    // should evaluate to: 13.6
    cout << "Evaluated: " << t->Evaluate() << endl;
    // (((2.3 * 1) + (X * 0)) + ((Y * (0 - 1)) + ((Z - X) * 0)))
    cout << "Derivative w.r.t. X: " << *(t->Derivative("X")) << endl;
    // derivative should evaluate to: -0.7
    cout << "Derivative Evaluated: " << t->Derivative("X")->Evaluate() << endl;

    cout << endl;
    delete t;
}