/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Player derived class that provides a simple AI poker player. Essentially
 *  bets 50 if the dealt hand is better than an Ace high, otherwise folds.
 **/

#include "BotPlayer.h"

using namespace std;

// ctor
BotPlayer::BotPlayer(string name, int startingChipCount) :
    Player(name, startingChipCount),
    thresholdHand(Card('A', 'S'), Card('6', 'S'), Card('5', 'S'), Card('4', 'S'), Card('3', 'C')),
    maxWillingToBet(50)
{
}

// logic for how much to bet, also updates amountBet
// simply just betting maxWillingToBet
int BotPlayer::bet() {
    setAmountBet(maxWillingToBet);
    return getAmountBet();
}

// logic for determining which action to take for the turn
// basically willing to bet maxWillingToBet if hand is better than thresholdHand, otherwise folds
Player::TurnAction BotPlayer::selectAction(int curMaxBet) {
    bool isHandBetterThanThreshold = (Hand::compareHands(getHand(), thresholdHand) < 0);

    if (isHandBetterThanThreshold) {
        if (curMaxBet < maxWillingToBet) {
            return Player::TurnAction::RAISE;
        }
        else if (curMaxBet == maxWillingToBet) {
            setAmountBet(curMaxBet);
            return Player::TurnAction::CALL;
        }
    }

    setIsFolded(true);
    return Player::TurnAction::FOLD;
}