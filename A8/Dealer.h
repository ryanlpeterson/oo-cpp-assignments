/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 **/

#include <string>
#include <array>
#include <vector>
#include "Card.h"

class Dealer
{
    public:

        // default ctor, initializes a dealer object
        Dealer();

        void createDeck();

        // shuffle the deck of cards
        void shuffle();

        // deal cards to players
        void deal();

    private:

        std::vector<Card> deck;
};