/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Card class that contains a card rank and suit
 **/

#ifndef CARD_H
#define CARD_H

#include <string>
#include <array>

class Card
{
    public:

        // default ctor, initializes a new card
        Card();

        // copy constructor
        Card(const Card &other);

        // ctor, initializes a new card with given rank and suit
        Card(char rank, char suit);

        // assignment operator
        Card& operator=(const Card& other);

        // returns the card rank
        char getRank() const;

        // returns the card suit
        char getSuit() const;

        // returns the value of the card
        int getValue() const;

        // returns the card rank and suit as a concatenated string
        std::string toString() const;

    private:

        // returns if card rank and suit is valid
        bool isValid(char rank, char suit) const;

        // array of possible card ranks
        const std::array<char, 13> cardRanks = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

        // array of card values
        const std::array<char, 13> cardValues = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

        // array of possible card suits
        const std::array<char, 4> cardSuits = {'C', 'S', 'H', 'D'};

        // Card's rank
        char cardRank;

        // Card's suit
        char cardSuit;

};
#endif