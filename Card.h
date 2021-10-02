/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 **/

class Card
{
    public:

        // default ctor, initializes a new card
        Card();

        // ctor, initializes a new card with given number and suit
        Card(char number, char suit);

        // function that returns the card number
        char getNumber();

        // function that returns the card suit
        char getSuit();

        int getValue();

        // function to print the card
        void print();

    private:

        // array of possible card numbers
        char cardNumbers[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

        // array of card values
        int cardValues[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

        // array of possible card suits
        char cardSuits[4] = {'C', 'S', 'H', 'D'};

        // Card's number
        char cardNumber;

        // Card's suit
        char cardSuit;

};