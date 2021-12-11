/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description:
 **/

#include "Player.h"

using namespace std;

Player::Player(bool isBot, string name) :
    isBot (isBot), name (name)
{
}

void Player::addCardToHand(Card card) {
    hand.addCardToHand(card);
}