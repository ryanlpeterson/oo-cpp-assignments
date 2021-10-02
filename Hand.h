/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 **/

#include "Card.h"
using namespace std;

class Hand
{
    public:

        Hand();

        Hand(Card card0, Card card1, Card card2, Card card3, Card card4);

        void sortHand();

        bool isRoyalFlush();

        bool isStraightFlush();

        bool isFourOfAKind();

        bool isFullHouse();

        bool isFlush();

        bool isStraight();

        bool isThreeOfAKind();

        bool isTwoPair();

        bool isOnePair();

        int getHighCard();

        void checkHandType();

        void print();

        void printHandType();

    private:

        enum HandType
        {
            ROYALFLUSH,
            STRAIGHTFLUSH,
            FOUROFAKIND,
            FULLHOUSE,
            FLUSH,
            STRAIGHT,
            THREEOFAKIND,
            TWOPAIR,
            ONEPAIR,
            HIGHCARD
        };

        // array of cards in the hand
        Card cards[5];

        // type of hand (flush, fullhouse, etc.)
        HandType handType;
};