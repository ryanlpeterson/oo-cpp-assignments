/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #5: Probability
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/17/2021
 * Description: This program provides an automated test interface for the Probability cpp file
 **/

#include <iostream>
#include "Probability.h"
using namespace std;

int main()
{
    // Create probabilities to use in testing
    Probability a { 0.3 };
    Probability b { 0.7 };
    b = 0.9;

    // Test constructor and assignment operator
    cout << "a = " << a.getValue() << endl;
    cout << "b = " << b.getValue() << endl;

    // Test probability of a not occurring
    cout << "~a = " << ~a << endl;

    // Test probability of a and b occurring
    cout << "a & b = " << (a & b) << endl;

    // Test probability of a or b occurring
    cout << "a | b = " << (a | b) << endl;

    // Test probability of a or b, but not both occurring
    cout << "a ^ b = " << (a ^ b) << endl;

    // Test probability of a but not b occurring
    cout << "a - b = " << (a - b) << endl;

    // Check constructor error bounds (exception becuase not between 0.0 and 1.0)
    try {
        Probability c { 1.1 };
    }
    catch (const exception& e) {
        cout << "Properly errored on invalid constructor use: " << e.what() << endl;
    }

    // Check assignment operator error bounds (exception becuase not between 0.0 and 1.0)
    Probability d { 0.5 };
    try {
        d = -0.1;
    }
    catch (const exception& e) {
        cout << "Properly errored on invalid assignment operator use: " << e.what() << endl;
    }
}