/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 * Description: This program provides an automated test interface for the Card and Hand cpp files using libconfig.
 **/

#include <iostream>
#include "Dealer.h"
using namespace std;

int main()
{
    Dealer dealer;

    dealer.createDeck();
    dealer.shuffle();
}