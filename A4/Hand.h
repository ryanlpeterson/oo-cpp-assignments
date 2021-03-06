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
        // Constructor to initialize the hand with the given cards
        Hand(Card card0, Card card1, Card card2, Card card3, Card card4);

        // Compares hands first based on hand type, if of the same type compares based on the ranks of cards in priority order
        // Returns less than 0 if hand1 ranks higher, returns greater than 0 if hand2 ranks higher, and returns 0 if hands rank the same
        static int compareHands(Hand hand1, Hand hand2);

        // Returns the hand as a formatted string
        std::string toString();

    private:
        // private member functions
        // Sort the hand in descending order based on card rank value
        void sortHand();

        // Determine the applicable highest ranking hand type
        void checkHandType();

        // The following functions determine if the hand is of the given type
        // The functions do not check that they are not a rarer hand type
        // The functions set the prioritySortedCards
        bool isRoyalFlush();
        bool isStraightFlush();
        bool isFourOfAKind();
        bool isFullHouse();
        bool isFlush();
        bool isStraight();
        bool isThreeOfAKind();
        bool isTwoPair();
        bool isOnePair();

        // private enum of all possible hand types
        // Must be listed in descending ranking for comparison
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

        // private instance variables
        // Array of cards in the hand
        std::array<Card, 5> cards;

        // Array of cards in the hand sorted based on priority given the hand type
        std::array<Card, 5> prioritySortedCards;

        // Type of hand (flush, fullhouse, etc.)
        HandType handType;
};