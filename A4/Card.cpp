
/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 * Description: Card class that contains a card number and suit
 **/

#include "Card.h"
using namespace std;

/**
 * Default constructor
 **/
Card::Card()
{

}

/**
 * Constructor to initialize the card with the given number and suit
 **/
Card::Card(char number, char suit)
{
    cardNumber = number;
    cardSuit = suit;
}

/**
 * Returns the card number
 **/
char Card::getNumber()
{
    return cardNumber;
}

/**
 * Returns the card suit
 **/
char Card::getSuit()
{
    return cardSuit;
}

/**
 * Returns the value of the card (2-14)
 **/
int Card::getValue()
{
    int cardNumbersLength = sizeof(cardNumbers) / sizeof(cardNumbers[0]);
    for (int i = 0; i < cardNumbersLength; ++i)
    {
        if (cardNumbers[i] == cardNumber)
        {
            return cardValues[i];
        }
    }
}

/**
 * Returns the card number and suit as a concatenated string
 **/
string Card::toString()
{
    string str;
    str += cardNumber;
    str += cardSuit;
    return str;
}