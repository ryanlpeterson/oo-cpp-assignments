/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #5: Probability
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/17/2021
 **/

class Probability
{
    public:
        Probability(double value = 0.0);

        const Probability& operator=(double value);

        double operator~();

        double getValue() const;

    private:
        double value;
};

double operator&(const Probability& left, const Probability& right);
double operator|(const Probability& left, const Probability& right);
double operator^(const Probability& left, const Probability& right);
double operator-(const Probability& left, const Probability& right);
