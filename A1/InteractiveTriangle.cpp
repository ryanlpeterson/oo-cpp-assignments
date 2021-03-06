/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #1: Triangle Test
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/05/2021
 * Description: This program provides a user driven test interface for Triangle.cpp.
 **/

#include <iostream>
#include "Triangle.h"
using namespace std;

int main()
{
    // Print welcome and instructions for the user
    std::cout << "Welcome to the Triangle Test \n";
    std::cout << "Enter values for the triangle's sides to determine the type of the triangle \n";

    // Create variables that will be used to store the user's input
    int side1;
    int side2; 
    int side3;

    // Get the values from the user
    std::cout << "Enter a value for side 1: ";
    std::cin >> side1;

    std::cout << "Enter a value for side 2: ";
    std::cin >> side2;

    std::cout << "Enter a value for side 3: ";
    std::cin >> side3;

    // Call function with the values from the user
    Triangle triangle;
    triangle.getTriangleType(side1, side2, side3);

    return 0;
}