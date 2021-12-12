/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description:
 **/

#include <iostream>
#include "InteractivePlayer.h"

using namespace std;

InteractivePlayer::InteractivePlayer(string name, int startingChipCount) :
    Player(false, name, startingChipCount)
{
}

int InteractivePlayer::bet() {
    cout << "Enter integer value willing to bet: ";
    int bet;
    cin >> bet;

    setAmountBet(bet);
    return getAmountBet();
}

// basically willing to bet maxWillingToBet if hand is better than thresholdHand, otherwise folds
Player::TurnAction InteractivePlayer::takeAction(int curMaxBet) {
    char action;
    do {
        cout << "Enter action to take (c|r|f) for CALL, RAISE, or FOLD respectfully: ";
        cin >> action;

        switch (action) {
            case 'c':
                setAmountBet(curMaxBet);
                return Player::TurnAction::CALL;
            case 'r':
                return Player::TurnAction::RAISE;
            case 'f':
                setIsFolded(true);
                return Player::TurnAction::FOLD;
            default:
                cout << "Invalid action. Please try again." << endl;
        }
    } while (true);
}