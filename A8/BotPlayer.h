/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Player derived class that provides a simple AI poker player. Essentially
 *  bets 50 if the dealt hand is better than an Ace high, otherwise folds.
 **/

#ifndef BOT_PLAYER_H
#define BOT_PLAYER_H

#include <string>
#include "Hand.h"
#include "Player.h"

class BotPlayer: public Player
{
    public:
        // ctor
        BotPlayer(std::string name, int startingChipCount);

        // logic for how much to bet, also updates amountBet
        int bet();

        // logic for determining which action to take for the turn
        TurnAction selectAction(int curMaxBet);

    private:
        // variables for AI logic
        // threshold hand that actual hand is compared to to determine actions and betting
        Hand thresholdHand;
        // amount willing to bet that influences actions and betting
        int maxWillingToBet;
};
#endif