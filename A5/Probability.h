/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #5: Probability
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/17/2021
 **/

class Probability
{
    public:
        // Constructor
        Probability(double value = 0.0);

        // Assignment operator
        const Probability& operator=(double value);

        // Probability of the event not occurring (1-value)
        double operator~();

        // Return the value
        double getValue() const;

    private:
        // The value associated with this probability.
        // Must be value between 0.0 and 1.0
        double value;
};

// Overload statements for operators &, |, ^, and -
double operator&(const Probability& left, const Probability& right);
double operator|(const Probability& left, const Probability& right);
double operator^(const Probability& left, const Probability& right);
double operator-(const Probability& left, const Probability& right);
