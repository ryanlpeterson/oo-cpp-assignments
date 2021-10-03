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
    Card card10 ('A', 'S');
    Card card11 ('9', 'C');
    Card card12 ('T', 'D');
    Card card13 ('K', 'D');
    Card card14 ('5', 'H');

    Hand hand1 (card10, card11, card12, card13, card14);
    hand1.print();

    cout << endl;

    Card card20('A', 'S');
    Card card21('9', 'C');
    Card card22('T', 'D');
    Card card23('Q', 'D');
    Card card24('5', 'H');

    Hand hand2(card20, card21, card22, card23, card24);
    hand2.print();

    cout << endl;
    cout << Hand::compareHands(hand1, hand2);
}