/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 **/

#include <deque>
#include <vector>
#include "Card.h"
#include "Player.h"

class Dealer
{
    public:
        // shuffle the deck of cards
        void shuffle(std::deque<Card>& deck);

        // deal cards to players
        void deal(std::deque<Card>& deck, std::vector<Player>& players);

    private:
        static const int MAX_HAND_SIZE = 5;
};