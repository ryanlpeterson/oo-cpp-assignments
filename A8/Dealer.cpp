/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Card class that contains a card rank and suit
 **/

#include "Dealer.h"
#include <iostream>
#include <time.h>

using namespace std;

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

void Dealer::deal(deque<Card>& deck, vector<std::shared_ptr<Player> > players) {
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        for (int j = 0; j < players.size(); j++) {
            if (players[j]->getChipCount() > 0) {
                players[j]->addCardToHand(deck.front());
                deck.pop_front();
            }
        }
    }
}

void Dealer::collectCardsFromPlayers(vector<std::shared_ptr<Player> > players) {
    for (int i = 0; i < players.size(); i++) {
        players[i]->discardHand();
    }
}