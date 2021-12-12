/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 **/

#ifndef INTERACTIVE_PLAYER_H
#define INTERACTIVE_PLAYER_H

#include <string>
#include "Hand.h"
#include "Player.h"

class InteractivePlayer: public Player
{
    public:
        InteractivePlayer(std::string name, int startingChipCount);

        int bet();

        TurnAction takeAction(int curMaxBet);

    private:
};
#endif