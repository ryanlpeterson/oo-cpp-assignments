/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Abstract base class that manages poker player information, such as
 *  the dealt hand, the amount of chips possessed, the amount of chips bet, and whether
 *  folded or not.
 **/

#include "Player.h"

using namespace std;

// ctor that accepts the player's name and how many chips they are starting with
Player::Player(string name, int startingChipCount) :
    name (name), chipCount (startingChipCount)
{
}

// default dtor, virtual because there are other virtual functions
Player::~Player() {
}

// adds a card to the hand if not at max capacity
void Player::addCardToHand(Card card) {
    hand.addCardToHand(card);
}

// clears the cards in the hand
void Player::discardHand() {
    hand.discardHand();
}

// return whether there are cards in the hand
bool Player::hasHand() const {
    return (hand.getNumCardsInHand() == 5);
}

// adds the given amount to the chipCount
void Player::awardChips(int chipAmount) {
    chipCount += chipAmount;
}

// deducts the given amount from the chipCount
void Player::takeChips(int chipAmount) {
    chipCount -= chipAmount;
}

// returns the player's name
string Player::getName() const {
    return name;
}
// returns the chip count
int Player::getChipCount() const {
    return chipCount;
}
// returns the amount bet so far this round
int Player::getAmountBet() const {
    return amountBet;
}
// sets the amount bet so far this round, up to a maximum of the available chip count
void Player::setAmountBet(int amountBet) {
    // can only bet as much as the player has
    if (amountBet < chipCount) {
        this->amountBet = amountBet;
    }
    else {
        this->amountBet = chipCount;
    }
}
// returns whether the player has folded this round
bool Player::getIsFolded() const {
    return isFolded;
}
// sets whether the player has folded this round
void Player::setIsFolded(bool isFolded) {
    this->isFolded = isFolded;
}
// returns the player's hand
const Hand& Player::getHand() const {
    return hand;
}