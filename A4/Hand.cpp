/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 * Description: Hand class that keeps track of cards in a player's hand and compares hands
 **/

#include "Hand.h"
#include <iostream>
using namespace std;

/**
 * Constructor to initialize the hand with the given cards
 **/
Hand::Hand(Card card0, Card card1, Card card2, Card card3, Card card4) :
    cards {card0, card1, card2, card3, card4}
{
    sortHand();
    checkHandType();
}

/**
 * Sort the hand in descending order based on card rank value
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

        if (highCard != i)
        {
            Card card = cards[i];
            cards[i] = cards[highCard];
            cards[highCard] = card;
        }
	}
}

/**
 * Determine the applicable highest ranking hand type
 * Hand types must be checked in descending priority, as more common types do not check that they are not a rarer type
 *  e.g. isOnePair() will return true if the hand contains a three of a kind, and isFlush() will return true if is a straight flush
 * Also sets the prioritySortedCards based on the hand type
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
    else
    {
        handType = Hand::HIGH_CARD;
        prioritySortedCards = cards;
        return;
    }
}

/**
 * Determine if the hand is a royal flush (A, K, Q, J, 10, all the same suit)
 **/
bool Hand::isRoyalFlush()
{
    // is a straight flush and the first card is an Ace
	if (isStraightFlush() && cards[0].getNumber() == 'A')
    {
        handType = Hand::ROYAL_FLUSH;
        // prioritySortedCards already set in isStraightFlush() check
		return true;
    }
	
    return false;
}

/**
 * Determine if the hand is a straight flush (five cards in a sequence, but not of the same suit)
 **/
bool Hand::isStraightFlush()
{
	if (isStraight() && isFlush())
    {
        handType = Hand::STRAIGHT_FLUSH;
        // prioritySortedCards already set in isStraight() check
		return true;
    }
	
    return false;
}

/**
 * Determine if the hand has four of a kind (four cards of the same rank)
 **/
bool Hand::isFourOfAKind()
{
    // if first four cards are the same
	if((cards[0].getValue() == cards[1].getValue()) && (cards[1].getValue() == cards[2].getValue()) && (cards[2].getValue() == cards[3].getValue()))
    {
        handType = Hand::FOUR_OF_A_KIND;
        prioritySortedCards = cards;
		return true;
    }
    // if last four cards are the same
	else if((cards[1].getValue() == cards[2].getValue()) && (cards[2].getValue() == cards[3].getValue()) && (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::FOUR_OF_A_KIND;
        prioritySortedCards = {cards[1], cards[2], cards[3], cards[4], cards[0]};
		return true;
    }
	
    return false;
}

/**
 * Determine if the hand is a full house (three of a kind and a pair)
 **/
bool Hand::isFullHouse()
{	
	if (((cards[0].getValue() == cards[1].getValue()) && (cards[1].getValue() == cards[2].getValue())) && (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::FULL_HOUSE;
        prioritySortedCards = cards;
		return true;
    }
	else if (((cards[2].getValue() == cards[3].getValue()) && (cards[3].getValue() == cards[4].getValue())) && (cards[0].getValue() == cards[1].getValue()))
    {
        handType = Hand::FULL_HOUSE;
        prioritySortedCards = {cards[2], cards[3], cards[4], cards[0], cards[1]};
		return true;
    }
	
    return false;
}

/**
 * Determine if the hand is a flush (five cards of the same suit, but not in a sequence)
 **/
bool Hand::isFlush()
{
    char suitOfFirst = cards[0].getSuit();

    // evaluate the card suits to determine if it's a flush
	for (int i = 1; i < 5; ++i)
    {
		if (cards[i].getSuit() != suitOfFirst)
        {
            return false;
        }
    }

    handType = Hand::FLUSH;
    prioritySortedCards = cards;
	return true;
}

/**
 * Determine if the hand is a straight (five cards in a sequence, but not the same suit)
 * Not considering 5432A as a straight here as rules can vary, only considering high rank ace straight, AKQJT
 **/
bool Hand::isStraight()
{
    // evaluate the card numbers to determine if it's a straight
	for (int i = 0; i < 4; ++i)
    {
		if ((cards[i].getValue()-1) != cards[i+1].getValue())
        {
            return false;
        }
    }

    handType = Hand::STRAIGHT;
    prioritySortedCards = cards;
	return true;
}

/**
 * Determine if the hand has three of a kind (three cards of the same rank)
 **/
bool Hand::isThreeOfAKind()
{
    // check if first three cards are the same
	if ((cards[0].getValue() == cards[1].getValue()) && (cards[1].getValue() == cards[2].getValue()))
    {
        handType = Hand::THREE_OF_A_KIND;
        prioritySortedCards = cards;
		return true;
    }
    // check if middle three cards are the same
	else if ((cards[1].getValue() == cards[2].getValue()) && (cards[2].getValue() == cards[3].getValue()))
    {
        handType = Hand::THREE_OF_A_KIND;
        prioritySortedCards = {cards[1], cards[2], cards[3], cards[0], cards[4]};
		return true;
    }
    // check if last three cards are the same
	else if ((cards[2].getValue() == cards[3].getValue()) && (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::THREE_OF_A_KIND;
        prioritySortedCards = {cards[2], cards[3], cards[4], cards[0], cards[1]};
		return true;
    }
	
    return false;
}

/**
 * Determine if the hand has two pairs (two different pairs of the same rank)
 **/
bool Hand::isTwoPair()
{
    // check if two pairs in first 4 cards (excluding last card)
	if ((cards[0].getValue() == cards[1].getValue()) && (cards[2].getValue() == cards[3].getValue()))
    {
        handType = Hand::TWO_PAIR;
        prioritySortedCards = cards;
		return true;
    }
    // check for two pairs in last 4 cards (excluding first card)
	else if ((cards[1].getValue() == cards[2].getValue()) && (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::TWO_PAIR;
        prioritySortedCards = {cards[1], cards[2], cards[3], cards[4], cards[0]};
		return true;
    }
    // check for two pairs in first and last cards (excluding middle card)
	else if ((cards[0].getValue() == cards[1].getValue()) && (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::TWO_PAIR;
        prioritySortedCards = {cards[0], cards[1], cards[3], cards[4], cards[2]};
		return true;
    }
	
    return false;
}

/**
 * Determine if the hand has one pair (one pair of the same rank)
 **/
bool Hand::isOnePair()
{
    std::array<Card, 5> possiblePrioritySortedCards;
    // first two positions are reserved for pair, singles will start at index 2
    int nonPairCardCursor = 2;

    // evaluate the card numbers to determine if it's a straight
    for (int i = 0; i < 5; ++i)
    {
        if ((i < 4) && (cards[i].getNumber() == cards[i + 1].getNumber()))
        {
            possiblePrioritySortedCards[0] = cards[i];
            possiblePrioritySortedCards[1] = cards[i + 1];
            // skip checking the next because it is the other part of the pair
            i++;
        }
        else
        {
            try
            {
                possiblePrioritySortedCards.at(nonPairCardCursor) = cards[i];
                nonPairCardCursor++;
            }
            catch (out_of_range const& exc)
            {
                // being here means no pair found
                return false;
            }
        }
    }

    // must have found pair
    handType = Hand::ONE_PAIR;
    prioritySortedCards = possiblePrioritySortedCards;
    return true;

    // TODO: delete this old way, or go back to this, split into "if else"s and get priority like other methods
	/*if ((cards[0].getValue() == cards[1].getValue()) || (cards[1].getValue() == cards[2].getValue()) || (cards[2].getValue() == cards[3].getValue()) || (cards[3].getValue() == cards[4].getValue()))
    {
        handType = Hand::ONEPAIR;
		return true;
    }
	else
    {
		return false;
    }*/
}

/**
 * Compares hands first based on hand type, if of the same type compares based on the ranks of cards in priority order
 * Returns less than 0 if hand1 ranks higher, returns greater than 0 if hand2 ranks higher, and returns 0 if hands rank the same
 **/
int Hand::compareHands(Hand hand1, Hand hand2)
{
    // lower handType value is better
    if (hand1.handType < hand2.handType)
    {
        return -1;
    }
    else if (hand1.handType > hand2.handType)
    {
        return 1;
    }

    // hands are of the same type, so go through comparing cards in priority order
    for (int i = 0; i < 5; ++i)
    {
        // higher card value is better
        if (hand1.prioritySortedCards[i].getValue() > hand2.prioritySortedCards[i].getValue())
        {
            return -1;
        }
        else if (hand1.prioritySortedCards[i].getValue() < hand2.prioritySortedCards[i].getValue())
        {
            return 1;
        }
        // cards are the same, continue to the next cards
    }

    // hands must be of equal rank
    return 0;
}

/**
 * Returns the hand as a formatted string
 **/
string Hand::toString()
{
    string str;
    str += "(";
    str += prioritySortedCards[0].toString();
    for (int i = 1; i < 5; ++i)
    {
        str += ", " + prioritySortedCards[i].toString();
    }
    str += ")";

    return str;
}