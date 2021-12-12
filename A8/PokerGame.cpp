/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description:
 **/

#include <iostream>
#include "Dealer.h"
#include "PokerGame.h"

using namespace std;

PokerGame::PokerGame(vector<std::shared_ptr<Player> > players) :
    players (players)
{
    initDeckTemplate();
}

void PokerGame::play() {
    cout << "==============================================================" << endl;
    cout << "Starting round..." << endl;
    cout << "Shuffling and dealing cards..." << endl;
    deque<Card> deck(deckTemplate);
    Dealer::shuffle(deck);
    Dealer::deal(deck, players);

    cout << "Starting betting..." << endl;
    cout << endl;
    int numPlayersOut = 0;
    for (int i = 0; i < players.size(); i++) {
        if (!players[i]->hasHand()) {
            numPlayersOut++;
        }
    }
    int numPlayersSinceNewBet = 0;
    int curPlayerIndex = 0;
    int curMaxBet = 0;
    while (numPlayersSinceNewBet < players.size() && numPlayersOut < players.size() - 1) {

        Player& curPlayer = *players[curPlayerIndex];

        if (!curPlayer.getIsFolded() && curPlayer.hasHand()) {
            // first print the latest game state info
            printGameState(curPlayerIndex);
            cout << endl;
            cout << curPlayer.getName() << "'s turn..." << endl;

            Player::TurnAction action = curPlayer.takeAction(curMaxBet);

            if (action == Player::TurnAction::RAISE) {
                int bet = curPlayer.bet();
                while (bet <= curMaxBet) {
                    cout << "Bet is not greater than the current max bet, please bet again." << endl;
                    bet = curPlayer.bet();
                }
                cout << curPlayer.getName() << " bet " << bet << "." << endl;
                curMaxBet = bet;

                numPlayersSinceNewBet = 0;
            }
            else if (action == Player::TurnAction::CALL) {
                cout << curPlayer.getName() << " called." << endl;
            }
            else if (action == Player::TurnAction::FOLD) {
                cout << curPlayer.getName() << " folded." << endl;
                numPlayersOut++;
            }

            cout << endl;
        }

        numPlayersSinceNewBet++;

        curPlayerIndex++;
        if (curPlayerIndex >= players.size()) {
            curPlayerIndex = 0;
        }
    }

    // first print the latest game state info
    cout << "Betting complete, calculating winner(s)..." << endl;
    printGameState(-1);
    cout << endl;

    // get pot value and get players that didn't fold
    int pot = 0;
    vector<std::shared_ptr<Player> > remainingPlayers;
    for (int i = 0; i < players.size(); i++) {
        int amountBet = players[i]->getAmountBet();
        // add chips to pot and take from player
        pot += amountBet;
        players[i]->takeChips(amountBet);
        if (!players[i]->getIsFolded()) {
            remainingPlayers.push_back(players[i]);
        }
    }

    // find winning player(s)
    // keep a running list of potential tie-ers
    vector<std::shared_ptr<Player> > potentiallyTieingPlayers;
    while (remainingPlayers.size() > 1) {
        int compareResult = Hand::compareHands(remainingPlayers[0]->getHand(), remainingPlayers[1]->getHand());
        if (compareResult < 0) {
            // first hand ranks higher, remove the second
            remainingPlayers.erase(remainingPlayers.begin() + 1);
        }
        else if (compareResult > 0) {
            // second hand ranks higher, remove the first
            remainingPlayers.erase(remainingPlayers.begin());
            // also clear any tie-ers that were being retained
            potentiallyTieingPlayers.clear();
        }
        else {
            // tie currently occuring, move one of players off to a separate list for now
            potentiallyTieingPlayers.push_back(remainingPlayers[0]);
            remainingPlayers.erase(remainingPlayers.begin());
        }
    }

    // output winner(s)
    cout << "Round winners: ";
    for (int i = 0; i < remainingPlayers.size() - 1; i++) {
        cout << remainingPlayers[i]->getName() << ", ";
    }
    cout << remainingPlayers.back()->getName() << endl;
    // output earnings
    // may be more than one winner so split pot
    int adjustedPot = pot / remainingPlayers.size();
    for (int i = 0; i < remainingPlayers.size(); i++) {
        Player& winningPlayer = *remainingPlayers[i];
        // player has already had their contribution to the pot taken away, so it won't be counted twice
        winningPlayer.awardChips(adjustedPot);

        cout << winningPlayer.getName() << " won " << adjustedPot << " chips" << endl;
    }

    // reset amount bet for players before printing final game state, for clarity
    for (int i = 0; i < players.size(); i++) {
        players[i]->setAmountBet(0);
    }

    // print final game state after round
    printGameState(-1);
    cout << endl;

    // collect all the cards back from players
    Dealer::collectCardsFromPlayers(players);
    // reset fold state for players
    for (int i = 0; i < players.size(); i++) {
        players[i]->setIsFolded(false);
    }
}

bool PokerGame::isMultiplePlayersWithChips() {
    int numPlayersWithChips = 0;
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getChipCount() > 0) {
            numPlayersWithChips++;
        }
    }

    return (numPlayersWithChips > 1);
}

void PokerGame::printGameState(int curPlayerIndex) {
    int pot = 0;
    for (int i = 0; i < players.size(); i++) {
        pot += players[i]->getAmountBet();
    }
    cout << "Total pot: " << pot << endl;

    for (int i = 0; i < players.size(); i++) {
        Player& player = *players[i];
        if (i == curPlayerIndex) {
            cout << "-> " << player.getName();
        }
        else {
            cout << "   " << player.getName();
        }

        if (player.hasHand()) {
            if (player.getIsFolded()) {
                cout << " (FOLDED)";
            }
            if (player.getChipCount() <= 0) {
                cout << " (BANKRUPT)";
            }
            cout << endl;
            cout << "Bet:  " << player.getAmountBet() << "/" << player.getChipCount() << endl;
            cout << "Hand: " << player.getHand().toString() << endl;
        }
        else {
            cout << " (BANKRUPT)" << endl;
        }
    }
}

void PokerGame::initDeckTemplate() {
    const std::array<char, 13> cardRanks = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
    const std::array<char, 4> cardSuits = { 'C', 'S', 'H', 'D' };

    for (int i = 0; i < sizeof(cardSuits); ++i) {
        for (int j = 0; j < sizeof(cardRanks); ++j) {
            deckTemplate.push_back(Card(cardRanks[j], cardSuits[i]));
        }
    }
}