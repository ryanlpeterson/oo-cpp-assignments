/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 **/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Hand.h"

class Player
{
    public:
        // TODO: probably move enum out to a separate file
        enum TurnAction {
            CALL,
            RAISE,
            FOLD
            // in this case, since there is only one round, there is never a reason to CHECK
        };

        Player(bool isBot, std::string name, int startingChipCount);

        virtual ~Player();

        //void reset();

        void addCardToHand(Card card);

        void discardHand();

        void awardChips(int chipAmount);
        void takeChips(int chipAmount);

        // getters and setters
        std::string getName() const;
        int getChipCount() const;
        int getAmountBet() const;
        void setAmountBet(int amountBet);
        bool getIsFolded() const;
        void setIsFolded(bool isFolded);
        const Hand& getHand() const;

        // pure virtual functions
        virtual int bet() = 0;
        virtual TurnAction takeAction(int curMaxBet) = 0;
        //virtual int bet();
        //virtual TurnAction takeAction(int curMaxBet);

    private:
        bool isBot;
        std::string name;

        int chipCount = 0;

        int amountBet = 0;
        bool isFolded = false;
        Hand hand;
};
#endif