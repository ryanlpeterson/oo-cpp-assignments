/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #4: Poker Hand Rankings
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 10/03/2021
 * Description: This program provides an automated test interface for the Card and Hand cpp files using libconfig.
 **/

#include <iostream>
#include <libconfig.h++>
#include "Hand.h"
using namespace std;
using namespace libconfig;

int main()
{
    Config cfg;
    // Read the file. If there is an error, report it and exit.
    try
    {
        cfg.readFile("poker_hands.cfg");
    }
    catch (const FileIOException& fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch (const ParseException& pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
            << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }

    try
    {
        const Setting& games = cfg.getRoot()["games"];
        // iterate over games sub lists
        for (int i = 0; i < games.getLength(); ++i)
        {
            const Setting& gamesSubList = games[i];
            // print out game sub list name
            cout << gamesSubList.getName() << endl;
            // iterate over games for the sub list
            for (int j = 0; j < gamesSubList.getLength(); ++j)
            {
                // get hands for the game
                const Setting& hand1Setting = gamesSubList[j]["hand1"];
                const Setting& hand2Setting = gamesSubList[j]["hand2"];

                // check each hand is of the necessary size
                if (hand1Setting.getLength() != 5 || hand2Setting.getLength() != 5)
                {
                    cout << "ERROR: Configured hands must have 5 cards" << endl;
                    return(EXIT_FAILURE);
                }

                // construct cards for each hand
                Card cards1[5];
                Card cards2[5];
                for (int k = 0; k < 5; ++k)
                {
                    // construct card for hand1
                    string cardStr1 = hand1Setting[k];
                    char rank1 = cardStr1.at(0);
                    char suit1 = cardStr1.at(1);
                    Card card1(rank1, suit1);
                    cards1[k] = card1;

                    // construct card for hand2
                    string cardStr2 = hand2Setting[k];
                    char rank2 = cardStr2.at(0);
                    char suit2 = cardStr2.at(1);
                    Card card2(rank2, suit2);
                    cards2[k] = card2;
                }

                // construct each hand
                Hand hand1(cards1[0], cards1[1], cards1[2], cards1[3], cards1[4]);
                Hand hand2(cards2[0], cards2[1], cards2[2], cards2[3], cards2[4]);

                // compare hands and output results
                int compareResult = Hand::compareHands(hand1, hand2);
                if (compareResult < 0)
                {
                    cout << hand1.toString() << " ranks higher than " << hand2.toString();
                }
                else if (compareResult > 0)
                {
                    cout << hand2.toString() << " ranks higher than " << hand1.toString();
                }
                else
                {
                    cout << hand1.toString() << " and " << hand2.toString();
                    cout << ", are of equal rank";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    catch (const SettingNotFoundException& nfex)
    {
        cout << "ERROR: Setting not found";
    }
}