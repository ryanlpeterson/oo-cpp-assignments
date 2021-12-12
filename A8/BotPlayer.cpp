/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description:
 **/

#include "BotPlayer.h"

using namespace std;

BotPlayer::BotPlayer(string name, int startingChipCount) :
    Player(true, name, startingChipCount),
    //thresholdHand(Card('5', 'S'), Card('5', 'C'), Card('A', 'S'), Card('K', 'S'), Card('Q', 'S')),
    thresholdHand(Card('A', 'S'), Card('6', 'S'), Card('5', 'S'), Card('4', 'S'), Card('3', 'C')),
    maxWillingToBet(50)
{
}

int BotPlayer::bet() {
    setAmountBet(maxWillingToBet);
    return getAmountBet();
}

// basically willing to bet maxWillingToBet if hand is better than thresholdHand, otherwise folds
Player::TurnAction BotPlayer::takeAction(int curMaxBet) {
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