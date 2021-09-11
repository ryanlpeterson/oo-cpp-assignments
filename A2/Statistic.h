/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #2: Statistical Class
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/12/2021
 **/

class Statistic
{
    public:
        // default ctor
        Statistic();

        // add an item to the statistics
        void add(double x);

        // get average
        double average() const;

        // get standard deviation
        double STD() const;

    private:
        // number of elements added to the sequence
        int numElements;
        // running sum of the sequence values
        double sum;
        // running sum of the squares of the sequence values
        double sumOfSquared;
};