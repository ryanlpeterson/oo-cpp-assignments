/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Static dealer class that helps shuffle decks, deal cards to players,
 *  and clear players' hands.
 **/

#ifndef DEALER_H
#define DEALER_H

#include <deque>
#include <memory>
#include <vector>
#include "Card.h"
#include "Player.h"

static class Dealer
{
    public:
        // shuffle the deck of cards
        static void shuffle(std::deque<Card>& deck);

        // deal cards to players
        static void deal(std::deque<Card>& deck, std::vector<std::shared_ptr<Player> > players);

        // collect cards back from players
        static void collectCardsFromPlayers(std::vector<std::shared_ptr<Player> > players);

    private:
        // none
};
#endif