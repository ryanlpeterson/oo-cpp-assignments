/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description:
 **/

#include "Player.h"

using namespace std;

Player::Player(bool isBot, string name, int startingChipCount) :
    isBot (isBot), name (name), chipCount (startingChipCount)
{
}

Player::~Player() {
}

//void Player::reset() {
//    amountBet = 0;
//    isFolded = false;
//    hand.discardHand();
//}

void Player::addCardToHand(Card card) {
    hand.addCardToHand(card);
}

void Player::discardHand() {
    hand.discardHand();
}

bool Player::hasHand() const {
    return (hand.getNumCardsInHand() == 5);
}

void Player::awardChips(int chipAmount) {
    chipCount += chipAmount;
}

void Player::takeChips(int chipAmount) {
    chipCount -= chipAmount;
}

string Player::getName() const {
    return name;
}

int Player::getChipCount() const {
    return chipCount;
}

int Player::getAmountBet() const {
    return amountBet;
}

void Player::setAmountBet(int amountBet) {
    // can only bet as much as the player has
    if (amountBet < chipCount) {
        this->amountBet = amountBet;
    }
    else {
        this->amountBet = chipCount;
    }
}

bool Player::getIsFolded() const {
    return isFolded;
}

void Player::setIsFolded(bool isFolded) {
    this->isFolded = isFolded;
}

const Hand& Player::getHand() const {
    return hand;
}

//int Player::bet() {
//    return 0;
//}
//
//Player::TurnAction Player::takeAction(int curMaxBet) {
//    return Player::TurnAction::FOLD;
//}