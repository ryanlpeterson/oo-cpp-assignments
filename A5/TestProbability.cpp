/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #5: Probability
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/17/2021
 * Description: This program provides an interactive test interface for the Probability cpp file.
 **/

#include <iostream>
#include "Probability.h"
using namespace std;

int main()
{
    Probability a = 0.3;
    Probability b = 0.9;

    cout << "a = " << a.getValue() << endl;
    cout << "b = " << b.getValue() << endl;
    cout << "~a = " << ~a << endl;
    cout << "a & b = " << (a & b) << endl;
    cout << "a | b = " << (a | b) << endl;
    cout << "a ^ b = " << (a ^ b) << endl;
    cout << "a - b = " << (a - b) << endl;
}