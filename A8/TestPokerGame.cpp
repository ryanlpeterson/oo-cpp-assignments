/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 * Description:
 **/

#include <iostream>
#include <vector>
#include "BotPlayer.h"
#include "Dealer.h"
#include "InteractivePlayer.h"
#include "Player.h"
#include "PokerGame.h"
using namespace std;

int main()
{
    vector<Player*> players;
    int startingChipCount = 100;
    
    // TODO: create players from user input
    players.push_back(new InteractivePlayer("John", startingChipCount));
    players.push_back(new InteractivePlayer("Halsey", startingChipCount));
    players.push_back(new BotPlayer("Cortana", startingChipCount));

    PokerGame pokerGame(players);

    bool playAgain = true;

    while (playAgain) {
        pokerGame.play();

        if (pokerGame.isMultiplePlayersWithChips()) {
            cout << "Would you like to play another round? Enter y to play again: ";
            char playAgainDecision;
            cin >> playAgainDecision;
            // taking anything accept 'y' as a no
            if (playAgainDecision != 'y') {
                playAgain = false;
            }
        }
        else {
            cout << "Game complete. Only 1 player remains with chips." << endl;
            playAgain = false;
        }
    }
}