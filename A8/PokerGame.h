/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Represents a poker game for a given list of players. Provides
 *  functionality to play one round/game for the given players. Ensures player state info
 *  is reset at the end of the round.
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
        // ctor that accepts the players "at the table"
        PokerGame(std::vector<std::shared_ptr<Player> > players);

        // plays one round of poker with the given players
        void play();

        // returns whether multiple players still have chips
        bool isMultiplePlayersWithChips() const;

        // outputs the current state of the game (pot and player info)
        void printGameState(int curPlayerIndex) const;

    private:
        // initializes the cards in a standard deck (no jokers)
        void initDeckTemplate();

        // list of the players "at the table"
        std::vector<std::shared_ptr<Player> > players;
        // cards in a standard deck (no jokers)
        // used as a spawn point for mutable deck copies
        std::deque<Card> deckTemplate;
};
#endif