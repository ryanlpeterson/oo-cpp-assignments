/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 **/

#include <string>

class Card
{
    public:

        // default ctor, initializes a new card
        Card();

        // ctor, initializes a new card with given rank and suit
        Card(char rank, char suit);

        // returns the card rank
        char getRank();

        // returns the card suit
        char getSuit();

        // returns the value of the card
        int getValue();

        // returns the card rank and suit as a concatenated string
        std::string toString();

    private:

        // returns if card rank and suit is valid
        bool isValid(char rank, char suit);

        // array of possible card ranks
        char cardRanks[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

        // array of card values
        int cardValues[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

        // array of possible card suits
        char cardSuits[4] = {'C', 'S', 'H', 'D'};

        // Card's rank
        char cardRank;

        // Card's suit
        char cardSuit;

};