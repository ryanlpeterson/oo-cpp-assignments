/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 **/

#include "Card.h"
#include <array>

class Hand
{
    public:

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

        void checkHandType();

        static int compareHands(Hand hand1, Hand hand2);

        void print();

        void printHandType();

    private:

        enum HandType
        {
            ROYAL_FLUSH,
            STRAIGHT_FLUSH,
            FOUR_OF_A_KIND,
            FULL_HOUSE,
            FLUSH,
            STRAIGHT,
            THREE_OF_A_KIND,
            TWO_PAIR,
            ONE_PAIR,
            HIGH_CARD
        };

        // array of cards in the hand
        std::array<Card, 5> cards;

        // array of cards in the hand sorted based on priority given the hand type
        std::array<Card, 5> prioritySortedCards;

        // type of hand (flush, fullhouse, etc.)
        HandType handType;
};