/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 **/

#ifndef BOT_PLAYER_H
#define BOT_PLAYER_H

#include <string>
#include "Hand.h"
#include "Player.h"

class BotPlayer: public Player
{
    public:
        BotPlayer(std::string name, int startingChipCount);

        int bet();

        TurnAction takeAction(int curMaxBet);

    private:
        Hand thresholdHand;
        int maxWillingToBet;
};
#endif