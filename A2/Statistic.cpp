/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #2: Statistical Class
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/12/2021
 * Description: Accumulates information about a sequence of numbers and
 *  calculates its average and standard deviation. Warnings are produced
 *  if calculations are attempted on an empty sequence.
 **/

#include <cmath>
#include <iostream>
#include "Statistic.h"
using namespace std;

/**
 * Default constructor. Initializes instance variables.
 **/
Statistic::Statistic()
{
    // initialize all values to 0
    numElements = 0;
    sum = 0.0;
    sumOfSquared = 0.0;
}

/**
 * Adds the given item to the sequence, updating instance variables.
 **/
void Statistic::add(double x)
{
    // increment the number of elements
    numElements++;
    // add to the sum
    sum += x;
    // add to the sum of squares
    sumOfSquared += x * x;
}

/**
 * Returns the average of the sequence.
 * Warns if the sequence is empty.
 **/
double Statistic::average() const
{
    if (numElements == 0)
    {
        // warn and fall through, which will return some nan/inf/-inf/undefined/0 result
        cout << "Average not supported on an empty sequence! Please add a number.\n";
    }
    // calculate and return average
    return sum / numElements;
}

/**
 * Returns the standard deviation of the sequence.
 * Warns if the sequence is empty.
 **/
double Statistic::STD() const
{
    if (numElements == 0)
    {
        // warn and fall through, which will return some nan/inf/-inf/undefined/0 result
        cout << "STD not supported on an empty sequence! Please add a number.\n";
    }
    else if (numElements == 1)
    {
        // standard deviation of any single element sequence is 0.0
        return 0.0;
    }

    // calculate and return standard deviation using the hint given in the assignment description
    return sqrt((sumOfSquared - (sum * sum / numElements)) / (numElements - 1));
}