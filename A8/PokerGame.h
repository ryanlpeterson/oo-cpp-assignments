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

class PokerGame
{
    public:
        PokerGame(std::vector<Player> players);

        void play();

    private:
        void initDeckTemplate();

        int potChipCount = 0;
        std::vector<Player> players;
        std::deque<Card> deckTemplate;
};