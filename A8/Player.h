/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 **/

#include <string>
#include "Hand.h"

class Player
{
    public:
        Player(bool isBot, string name);

        void addCardToHand(Card card);

    private:
        bool isBot = true;
        string name;

        int chipCount = 0;

        int amountBetThisRound = 0;
        bool isFolded = false;
        Hand hand;
};