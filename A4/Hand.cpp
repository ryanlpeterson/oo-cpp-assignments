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
 * Constructor to initialize the hand with the given cards
 **/
Hand::Hand(Card card0, Card card1, Card card2, Card card3, Card card4) :
    cards {card0, card1, card2, card3, card4}
{
    sortHand();
    checkHandType();
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

        if (highCard != i)
        {
            Card card = cards[i];
            cards[i] = cards[highCard];
            cards[highCard] = card;
        }
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
    for (int i = 0; i < 4; ++i)
    {
        if (cards[i].getNumber() == cards[i + 1].getNumber())
        {
            possiblePrioritySortedCards[0] = cards[i];
            possiblePrioritySortedCards[1] = cards[i + 1];
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

    // TODO: delete this old way
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
    else
    {
        handType = Hand::HIGH_CARD;
        prioritySortedCards = cards;
        return;
    }
}

/**
 * Function to compare
 **/
int Hand::compareHands(Hand hand1, Hand hand2)
{
    //int hand1HandTypeScore = hand1.handType;
    //int hand2HandTypeScore = hand2.handType;

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
        // cards are the same, continue
    }

    // hands must be the exact same
    return 0;
}

/**
 * Function to print each card in the hand and the hand type
 **/
void Hand::print()
{
    cout << "(";
    cards[0].print();
    for (int i = 1; i < 5; ++i)
    {
        cout << ", ";
        cards[i].print();
    }
    cout << ") ";

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
        case Hand::STRAIGHT_FLUSH:
        {
            cout << "Straight Flush";
            break;
        }
        case Hand::FOUR_OF_A_KIND:
        {
            cout << "Four of a Kind";
            break;
        }
        case Hand::FULL_HOUSE:
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
        case Hand::THREE_OF_A_KIND:
        {
            cout << "Three of a Kind";
            break;
        }
        case Hand::TWO_PAIR:
        {
            cout << "Two Pair";
            break;
        }
        case Hand::ONE_PAIR:
        {
            cout << "One Pair";
            break;
        }
        case Hand::HIGH_CARD:
        {
            cout << "High Card";
            break;
        }
    }
}