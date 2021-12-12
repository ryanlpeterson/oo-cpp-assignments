/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 **/

#ifndef POKER_GAME_H
#define POKER_GAME_H

#include <deque>
#include <memory>
#include <vector>
#include "Card.h"
#include "Player.h"

class PokerGame
{
    public:

        PokerGame(std::vector<std::shared_ptr<Player> > players);

        void play();

        bool isMultiplePlayersWithChips();

        void printGameState(int curPlayerIndex);

    private:
        void initDeckTemplate();

        std::vector<std::shared_ptr<Player> > players;
        std::deque<Card> deckTemplate;
};
#endif