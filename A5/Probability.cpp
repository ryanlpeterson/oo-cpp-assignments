/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #5: Probability
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/17/2021
 * Description: Class that implements the probability of independent events
 **/

#include "Probability.h"
#include <stdexcept>
using namespace std;

// Constructor
Probability::Probability(double value) :
    // Check if value is within bounds (0.0-1.0)
    value (
        (value >= 0.0 && value <= 1.0) ? value :
            throw invalid_argument("Probability must be a value between 0.0 and 1.0")
    )
{

}

// Assignment operator
const Probability& Probability::operator=(double value) {
    // Check if new value is within bounds (0.0-1.0)
    this->value = (value >= 0.0 && value <= 1.0) ? value :
            throw invalid_argument("Probability must be a value between 0.0 and 1.0");

    return *this;
}

// Probability of the event not occurring
double Probability::operator~() {
    return 1 - value;
}

// Return the value
double Probability::getValue() const {
    return value;
}

// Probability of both events occuring
double operator&(const Probability& left, const Probability& right) {
    return left.getValue() * right.getValue();
}

// Probability of either left or right occurring
double operator|(const Probability& left, const Probability& right) {
    return left.getValue() + right.getValue() - (left & right);
}

// Probability of either left or right, but not both occurring
double operator^(const Probability& left, const Probability& right) {
    return (left | right) - (left & right);
}

// Probability of left but not right occurring
double operator-(const Probability& left, const Probability& right) {
    return left.getValue() - (left & right);
}