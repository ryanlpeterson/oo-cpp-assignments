/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 * Description: Hand class that keeps track of cards in a player's hand and compares hands
 **/

#include <iostream>
#include "Hand.h"
using namespace std;

/**
 * Default constructor
 **/
Hand::Hand()
{

}

/**
 * Constructor to initialize the hand with the given cards
 **/
Hand::Hand(Card card0, Card card1, Card card2, Card card3, Card card4)
{
    cards[0] = card0;
    cards[1] = card1;
    cards[2] = card2;
    cards[3] = card3;
    cards[4] = card4;
}

/**
 * Sort the hand (highest to lowest card values)
 **/
void Hand::sortHand()
{
    for(int i = 0; i < 4; ++i)	
	{
		int highCard = i;

		for (int j = i+1; j < 5; j++)
		{
			if(cards[j].getValue() > cards[highCard].getValue())
				highCard = j;
		}

		Card card = cards[i];
		cards[i] = cards[highCard];
		cards[highCard] = card;
	}
}

/**
 * Determine if the hand is a royal flush (A, K, Q, J, 10, all the same suit)
 **/
bool Hand::isRoyalFlush()
{
    // is a straight flush and the first card is an Ace
	if (isStraightFlush() && cards[0].getValue()== 14)
    {
        handType = Hand::ROYALFLUSH;
		return true;
    }
	else
    {
		return false;
    }
}

/**
 * Determine if the hand is a straight flush (five cards in a sequence, but not of the same suit)
 **/
bool Hand::isStraightFlush()
{
	if (isStraight() && isFlush())
    {
        handType = Hand::STRAIGHTFLUSH;
		return true;
    }
	else
    {
		return false;
    }
}

/**
 * Determine if the hand has four of a kind (four cards of the same rank)
 **/
bool Hand::isFourOfAKind()
{
    // if first four cards are the same
	if((cards[0].getValue() == cards[1].getValue()) && (cards[1].getValue() == cards[2].getValue()) && (cards[2].getValue() == cards[3].getValue()))
    {
        handType = Hand::FOUROFAKIND;
		return true;
    }
    // if last four cards are the same
	else if((cards[1].getValue() == cards[2].getValue()) && (cards[2].getValue() == cards[3].getValue()) && (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::FOUROFAKIND;
		return true;
    }
	else
    {
		return false;
    }
}

/**
 * Determine if the hand is a full house (three of a kind and a pair)
 **/
bool Hand::isFullHouse()
{	
	if (((cards[0].getValue() == cards[1].getValue()) && (cards[1].getValue() == cards[2].getValue())) && (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::FULLHOUSE;
		return true;
    }
	else if (((cards[2].getValue() == cards[3].getValue()) && (cards[3].getValue() == cards[4].getValue())) && (cards[0].getValue() == cards[1].getValue()))
    {
        handType = Hand::FULLHOUSE;
		return true;
    }
	else
    {
		return false;
    }
}

/**
 * Determine if the hand is a flush (five cards of the same suit, but not in a sequence)
 **/
bool Hand::isFlush()
{
    bool flush;

    // evaluate the card suits to determine if it's a flush
	for (int i = 0; i < 4; ++i)
    {
		if (cards[i].getSuit() == cards[i+1].getSuit())
        {
            handType = Hand::FLUSH;
			flush = true;
        }
		else
		{
			flush = false;
			break;
		}
    }

	return flush;
}

/**
 * Determine if the hand is a straight (five cards in a sequence, but not the same suit)
 **/
bool Hand::isStraight()
{
    bool straight;

    // evaluate the card numbers to determine if it's a straight
	for (int i = 0; i < 4; ++i)
    {
		if ((cards[i].getValue()-1) == cards[i+1].getValue())
        {
            handType = Hand::STRAIGHT;
			straight = true;
        }
		else
		{
			straight = false;
			break;
		}
    }

	return straight;
}

/**
 * Determine if the hand has three of a kind (three cards of the same rank)
 **/
bool Hand::isThreeOfAKind()
{
    // check if first three cards are the same
	if ((cards[0].getValue() == cards[1].getValue()) && (cards[1].getValue() == cards[2].getValue()))
    {
        handType = Hand::THREEOFAKIND;
		return true;
    }
    // check if middle three cards are the same
	else if ((cards[1].getValue() == cards[2].getValue()) && (cards[2].getValue() == cards[3].getValue()))
    {
        handType = Hand::THREEOFAKIND;
		return true;
    }
    // check if last three cards are the same
	else if ((cards[2].getValue() == cards[3].getValue()) && (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::THREEOFAKIND;
		return true;
    }
	else
    {
		return false;	
    }
}

/**
 * Determine if the hand has two pairs (two different pairs of the same number)
 **/
bool Hand::isTwoPair()
{
    // check if two pairs in first 4 cards (excluding last card)
	if ((cards[0].getValue() == cards[1].getValue()) && (cards[2].getValue() == cards[3].getValue()))
    {
        handType = Hand::TWOPAIR;
		return true;
    }
    // check for two pairs in middle 4 cards (excluding first card)
	else if ((cards[1].getValue() == cards[2].getValue()) && (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::TWOPAIR;
		return true;
    }
    // check for two pairs in first and last cards (excluding middle card)
	else if ((cards[0].getValue() == cards[1].getValue()) && (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::TWOPAIR;
		return true;
    }
	else
    {
		return false;
    }
}

/**
 * Determine if the hand has three of a kind (three cards of the same rank)
 **/
bool Hand::isOnePair()
{
	if ((cards[0].getValue() == cards[1].getValue()) || (cards[1].getValue() == cards[2].getValue()) || (cards[2].getValue() == cards[3].getValue()) || (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::ONEPAIR;
		return true;
    }
	else
    {
		return false;
    }
}

/**
 * Returns the highest card in the hand
 **/
int Hand::getHighCard()
{
    return cards[0].getValue();
}

/**
 * Checks the hand for all possible hand types
 **/
void Hand::checkHandType()
{
    if (isRoyalFlush())
    {
		return;
    }
	else if (isStraightFlush())
    {
		return;
    }
	else if (isFourOfAKind())
    {
		return;
    }
	else if (isFullHouse())
    {
		return;
    }
	else if (isFlush())
    {
		return;
    }
	else if (isStraight())
    {
		return;
    }
	else if (isThreeOfAKind())
    {
        return;
    }
	else if (isTwoPair())
    {
        return;
    }
	else if (isOnePair())
    {
        return;
    }
}

/**
 * Function to print each card in the hand and the hand type
 **/
void Hand::print()
{
    for (int i = 0; i < 5; ++i)
    {
        cards[i].print();
    }

    printHandType();
}

/**
 * Function to print the hand type (flush, straight, etc.)
 **/
void Hand::printHandType()
{
    cout << "Hand Type: ";

    switch (handType)
    {
        case Hand::STRAIGHTFLUSH:
        {
            cout << "Straight Flush";
            break;
        }
        case Hand::FOUROFAKIND:
        {
            cout << "Four of a Kind";
            break;
        }
        case Hand::FULLHOUSE:
        {
            cout << "Full House";
            break;
        }
        case Hand::FLUSH:
        {
            cout << "Flush";
            break;
        }
        case Hand::STRAIGHT:
        {
            cout << "Straight";
            break;
        }
        case Hand::THREEOFAKIND:
        {
            cout << "Three of a Kind";
            break;
        }
        case Hand::TWOPAIR:
        {
            cout << "Two Pair";
            break;
        }
        case Hand::ONEPAIR:
        {
            cout << "One Pair";
            break;
        }
        case Hand::HIGHCARD:
        {
            cout << "High Card";
            break;
        }
    }
}