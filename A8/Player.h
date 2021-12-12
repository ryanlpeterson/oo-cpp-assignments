/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Abstract base class that manages poker player information, such as
 *  the dealt hand, the amount of chips possessed, the amount of chips bet, and whether
 *  folded or not.
 **/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Hand.h"

class Player
{
    public:
        // enum of potential actions a user may make for a turn
        enum TurnAction {
            // bet the current max bet for the round
            CALL,
            // bet some new amount more than the current max bet for the round
            RAISE,
            // drop out of the round, no additional bet, may loose existing bets
            FOLD
            // in this case, since there is only one round, there is never a reason to CHECK
        };

        // ctor
        Player(std::string name, int startingChipCount);
        // default dtor, virtual because there are other virtual functions
        virtual ~Player();
        
        // adds a card to the hand if not at max capacity
        void addCardToHand(Card card);
        // clears the cards in the hand
        void discardHand();
        // return whether there are cards in the hand
        bool hasHand() const;

        // adds the given amount to the chipCount
        void awardChips(int chipAmount);
        // deducts the given amount from the chipCount
        void takeChips(int chipAmount);

        // necessary simple getters and setters
        std::string getName() const;
        int getChipCount() const;
        int getAmountBet() const;
        // set amount will max at available chipCount
        void setAmountBet(int amountBet);
        bool getIsFolded() const;
        void setIsFolded(bool isFolded);
        const Hand& getHand() const;

        // pure virtual functions
        // returns how much to bet and sets amount bet
        virtual int bet() = 0;
        // returns which action to take for the turn
        virtual TurnAction selectAction(int curMaxBet) = 0;

    private:
        // variables retained across rounds
        // name of the player
        std::string name;
        // current personal amount of chips, still includes amount bet so far this round
        int chipCount = 0;

        // per round variables
        // amount bet so far this round
        int amountBet = 0;
        // whether the player has folded this round
        bool isFolded = false;
        // the hand of 5 cards dealt this round
        Hand hand;
};
#endif