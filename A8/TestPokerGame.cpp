/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 * Description:
 **/

#include <iostream>
#include <vector>
#include "Dealer.h"
#include "Player.h"
#include "PokerGame.h"
using namespace std;

int main()
{
    vector<Player> players;
    
    // TODO: create players from user input
    players.push_back(Player(false, "John"));
    players.push_back(Player(true, "Cortana"));

    PokerGame pokerGame(players);
    pokerGame.play();
}