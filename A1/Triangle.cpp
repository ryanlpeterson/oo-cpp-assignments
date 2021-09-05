/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #1: Triangle Test
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/05/2021
 * Description: This program will read in 3 integer values from the user. Those values
 * will be assumed to be sides of a triangle. The getTriangleType function will be called
 * using the values given. The getTriangleType function will determine and print out if
 * the triangle is equilateral (three sides equal), isosceles (two sides equal), or
 * scalene (no sides equal). 
 **/

#include <iostream>
#include <string>
#include "Triangle.h"
using namespace std;


/**
 * Given the values for the three sides of a triangle, this function determines
 * and prints the type of the triangle (equilateral, isosceles, or scalene)
 **/
void Triangle::getTriangleType(int side1, int side2, int side3)
{
    std:cout << "Getting type for triangle with sides {"
        + std::to_string(side1)+ ", "
        + std::to_string(side2) + ", "
        + std::to_string(side3) + "}: \n";

    // Return if any sides are non-positive because the input is invalid
    if ((side1 <= 0) || (side2 <= 0) || (side3 <= 0))
    {
        std::cout << "Non-positive side values are invalid \n";
        return;
    }

    // Check if all sides are equal (equilateral)
    if ((side1 == side2) && (side2 == side3))
    {
        std::cout << "This is an equilateral triangle \n";
    }
    // Check if two sides are equal (isosceles)
    else if ((side1 == side2) || (side1 == side3) || (side2 == side3))
    {
        std::cout << "This is an isosceles triangle \n";
    }
    // Otherwise, no sides are equal (scalene)
    else
    {
        std::cout << "This is a scalene triangle \n";
    }
}