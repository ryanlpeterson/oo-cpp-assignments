/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Player derived class that prompts the user for decisions on
 *  actions and bets.
 **/

#ifndef INTERACTIVE_PLAYER_H
#define INTERACTIVE_PLAYER_H

#include <string>
#include "Hand.h"
#include "Player.h"

class InteractivePlayer: public Player
{
    public:
        // ctor
        InteractivePlayer(std::string name, int startingChipCount);

        // prompts user for how much to bet
        int bet();

        // prompts user for which action to take
        TurnAction selectAction(int curMaxBet);

    private:
        // none
};
#endif