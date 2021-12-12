/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 * Description: Provides a test interface for PokerGame. Level of interaction depends on the
 *  types of players defined.
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
    // initialize players
    // could be enhanced to let the user input player info, but for testing just going to hard code players
    vector<std::shared_ptr<Player>> players;
    int startingChipCount = 100;
    players.push_back(make_shared<InteractivePlayer>("John", startingChipCount));
    players.push_back(make_shared<InteractivePlayer>("Halsey", startingChipCount));
    players.push_back(make_shared<BotPlayer>("Cortana", startingChipCount));

    // init the poker game with the players
    PokerGame pokerGame(players);

    // keep playing rounds until either the user selects to stop or only one player remains with chips
    bool playAgain = true;
    while (playAgain) {
        // play a round
        pokerGame.play();

        if (pokerGame.isMultiplePlayersWithChips()) {
            // determine if the user would like to stop
            cout << "Would you like to play another round? Enter y to play again: ";
            char playAgainDecision;
            cin >> playAgainDecision;
            // taking anything accept 'y' as a no
            if (playAgainDecision != 'y') {
                playAgain = false;
            }
        }
        else {
            // only one player remains with chips, so stopping
            cout << "Game complete. Only 1 player remains with chips." << endl;
            playAgain = false;
        }
    }
}