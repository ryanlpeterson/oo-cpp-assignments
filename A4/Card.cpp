/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 * Description: Card class that contains a card rank and suit
 **/

#include "Card.h"
#include <iostream>
using namespace std;

/**
 * Default constructor
 **/
Card::Card()
{

}

/**
 * Constructor to initialize the card with the given rank and suit
 **/
Card::Card(char rank, char suit)
{
    if (isValid(rank, suit))
    {
        cardRank = rank;
        cardSuit = suit;
    }
    else
    {
        cout << "Please enter a valid card rank and suit";
        return;
    }
}

/**
 * Returns the card rank
 **/
char Card::getRank()
{
    return cardRank;
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
    int cardRanksLength = sizeof(cardRanks) / sizeof(cardRanks[0]);
    for (int i = 0; i < cardRanksLength; ++i)
    {
        if (cardRanks[i] == cardRank)
        {
            return cardValues[i];
        }
    }
}

/**
 * Returns the card rank and suit as a concatenated string
 **/
string Card::toString()
{
    string str;
    str += cardRank;
    str += cardSuit;
    return str;
}

/**
 * Returns if card rank and suit are valid
 **/
bool Card::isValid(char rank, char suit)
{
    bool rankValid = false;
    bool suitValid = false;
    int cardRanksLength = sizeof(cardRanks) / sizeof(cardRanks[0]);
    int cardSuitLength = sizeof(cardSuits) / sizeof(cardSuits[0]);

    // check if rank is valid
    for (int i = 0; i < cardRanksLength; ++i)
    {
        if (cardRanks[i] == rank)
        {
            rankValid = true;
            break;
        }
    }

    // check if suit is valid
    for (int i = 0; i < cardSuitLength; ++i)
    {
        if (cardSuits[i] == suit)
        {
            suitValid = true;
            break;
        }
    }

    return rankValid && suitValid;
}