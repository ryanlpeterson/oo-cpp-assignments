/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description:
 **/

#include "PokerGame.h"

using namespace std;

PokerGame::PokerGame(vector<Player> players) :
    players (players)
{
    initDeckTemplate();
}

void PokerGame::play() {

}

void PokerGame::initDeckTemplate() {
    const std::array<char, 13> cardRanks = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
    const std::array<char, 4> cardSuits = { 'C', 'S', 'H', 'D' };

    for (int i = 0; i < sizeof(cardSuits); ++i) {
        for (int j = 0; j < sizeof(cardRanks); ++j) {
            deckTemplate.push_back(Card(cardRanks[j], cardSuits[i]));
        }
    }
}