/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #1: Triangle Test
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/05/2021
 * Description: This program provides some automated test cases for Triangle.cpp.
 **/

#include "Triangle.h"
using namespace std;

int main()
{
    // Instance of triangle that will be used for testing
    Triangle triangle;

    // isosceles
    triangle.getTriangleType(3, 4, 3);
    // scalene
    triangle.getTriangleType(3, 4, 5);
    //equilateral
    triangle.getTriangleType(3, 3, 3);
    // invalid
    triangle.getTriangleType(3, 4, -1);
    // invalid
    triangle.getTriangleType(0, 4, 5);
    
    return 0;
}