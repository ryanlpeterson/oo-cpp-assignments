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

/**
 * Default constructor
 **/
Dealer::Dealer() 
{

}

void Dealer::createDeck() 
{
    const std::array<char, 13> cardRanks = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const std::array<char, 4> cardSuits = {'C', 'S', 'H', 'D'};

    for (int i = 0; i < sizeof(cardSuits); ++i) {
        for (int j = 0; j < sizeof(cardRanks); ++j) {
            deck.push_back(Card(cardRanks[j], cardSuits[i]));
        }
    }
}

void Dealer::shuffle() 
{
    // Use a different seed value so that
    // we don't get same result each time
    // we run this program
    srand (time(NULL));

    int n = deck.size();
 
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::swap(deck[i], deck[j]);
    }
}

void Dealer::deal() {

}
