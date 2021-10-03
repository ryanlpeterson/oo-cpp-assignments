/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 * Description: This program provides an interactive test interface for the Card and Hand cpp files.
 **/

#include <iostream>
#include "Hand.h"
using namespace std;

int main()
{
    Card card0 ('A', 'S');
    Card card1 ('9', 'C');
    Card card2 ('T', 'D');
    Card card3 ('Q', 'D');
    Card card4 ('5', 'H');

    Hand hand (card0, card1, card2, card3, card4);
    hand.sortHand();
    hand.checkHandType();
    hand.print();
}