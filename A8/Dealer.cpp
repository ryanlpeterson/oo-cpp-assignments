/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Static dealer class that helps shuffle decks, deal cards to players,
 *  and clear players' hands.
 **/

#include "Dealer.h"
#include <iostream>
#include <time.h>

using namespace std;

// shuffle the deck of cards
void Dealer::shuffle(deque<Card>& deck)
{
    // Use a different seed value so that
    // we don't get same result each time
    // we run this program
    srand(time(NULL));

    int n = deck.size();
 
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::swap(deck[i], deck[j]);
    }
}

// deal 5 cards to each player that has a chip count
// removes cards from deck
// adds cards to players' hands
void Dealer::deal(deque<Card>& deck, vector<std::shared_ptr<Player> > players) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < players.size(); j++) {
            if (players[j]->getChipCount() > 0) {
                players[j]->addCardToHand(deck.front());
                deck.pop_front();
            }
        }
    }
}

// collect cards back from players, clearing their hands
void Dealer::collectCardsFromPlayers(vector<std::shared_ptr<Player> > players) {
    for (int i = 0; i < players.size(); i++) {
        players[i]->discardHand();
    }
}