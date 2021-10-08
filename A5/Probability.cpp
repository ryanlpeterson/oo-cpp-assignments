/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #5: Probability
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/17/2021
 * Description: 
 **/

#include "Probability.h"
#include <stdexcept>
using namespace std;

Probability::Probability(double value) :
    value (
        (value >= 0.0 && value <= 1.0) ? value :
            throw invalid_argument("Probability must be a value between 0.0 and 1.0")
    )
{

}

const Probability& Probability::operator=(double value) {
    this->value = value;

    return *this;
}

double Probability::operator~() {
    return 1 - value;
}

double Probability::getValue() const {
    return value;
}

double operator&(const Probability& left, const Probability& right) {
    return left.getValue() * right.getValue();
}

double operator|(const Probability& left, const Probability& right) {
    return left.getValue() + right.getValue() - (left & right);
}

double operator^(const Probability& left, const Probability& right) {
    return (left | right) - (left & right);
}

double operator-(const Probability& left, const Probability& right) {
    return left.getValue() - (left & right);
}