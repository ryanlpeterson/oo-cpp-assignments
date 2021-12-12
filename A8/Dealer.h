/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 **/

#ifndef DEALER_H
#define DEALER_H

#include <deque>
#include <vector>
#include "Card.h"
#include "Player.h"

static class Dealer
{
    public:
        // shuffle the deck of cards
        static void shuffle(std::deque<Card>& deck);

        // deal cards to players
        static void deal(std::deque<Card>& deck, std::vector<Player*> players);

        // collect cards back from players
        static void collectCardsFromPlayers(std::vector<Player*> players);

    private:
        static const int MAX_HAND_SIZE = 5;
};
#endif