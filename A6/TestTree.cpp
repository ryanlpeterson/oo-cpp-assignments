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
using namespace std;

int main()
{
    Tree t = Add(Constant(1.2), Constant(1.0));
    cout << t.Evaluate();
}