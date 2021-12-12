/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #8: Poker Game
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 12/12/2021
 * Description: Represents a poker game for a given list of players. Provides
 *  functionality to play one round/game for the given players. Ensures player state info
 *  is reset at the end of the round.
 **/

#include <iostream>
#include "Dealer.h"
#include "PokerGame.h"

using namespace std;

// ctor that accepts the players "at the table"
PokerGame::PokerGame(vector<std::shared_ptr<Player> > players) :
    players (players)
{
    initDeckTemplate();
}

// plays one round of poker with the given players
// outputs the game state as it changes
// ensures player "per round" variables are reset after the round is complete
void PokerGame::play() {
    // setup for round
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
    // start collecting player actions and potential bets until betting is complete
    // betting is complete once a round has been made and the curMaxBet hasn't changed
    while (numPlayersSinceNewBet < players.size() && numPlayersOut < players.size() - 1) {
        // alias current player whose turn it is
        Player& curPlayer = *players[curPlayerIndex];

        // if player was dealt a hand and they haven't folded, collect their action and potentially their bet
        if (curPlayer.hasHand() && !curPlayer.getIsFolded()) {
            // first print the latest game state info
            printGameState(curPlayerIndex);
            cout << endl;
            cout << curPlayer.getName() << "'s turn..." << endl;

            // collect the player's action
            Player::TurnAction action = curPlayer.selectAction(curMaxBet);

            if (action == Player::TurnAction::RAISE) {
                // player wants to place a new higher bet, so collect bet
                int bet = curPlayer.bet();
                while (bet <= curMaxBet) {
                    cout << "Bet is not greater than the current max bet, please bet again." << endl;
                    bet = curPlayer.bet();
                }
                cout << curPlayer.getName() << " bet " << bet << "." << endl;
                curMaxBet = bet;

                // reset count for determining when betting round is over
                numPlayersSinceNewBet = 0;
            }
            else if (action == Player::TurnAction::CALL) {
                // player called, personal bet state info was updated in selectAction and bet functions
                cout << curPlayer.getName() << " called." << endl;
            }
            else if (action == Player::TurnAction::FOLD) {
                // player folded, personal fold state was updated in selectAction
                cout << curPlayer.getName() << " folded." << endl;
                numPlayersOut++;
            }

            cout << endl;
        }

        numPlayersSinceNewBet++;

        // iterate to the next person at the table
        curPlayerIndex++;
        if (curPlayerIndex >= players.size()) {
            curPlayerIndex = 0;
        }
    }

    // print the post-betting game state info
    cout << "Betting complete, calculating winner(s)..." << endl;
    printGameState(-1);
    cout << endl;

    // need to determine winner(s) and update player chip counts
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

    // find winner(s)
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
    // add any potential tie-ers back to the remaining player's list as they are winners
    remainingPlayers.insert(remainingPlayers.end(), potentiallyTieingPlayers.begin(), potentiallyTieingPlayers.end());

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

    // reset amount bet for players before printing final game state, for interpretation clarity
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

// returns whether multiple players still have chips
bool PokerGame::isMultiplePlayersWithChips() const {
    int numPlayersWithChips = 0;
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getChipCount() > 0) {
            numPlayersWithChips++;
        }
    }

    return (numPlayersWithChips > 1);
}

// outputs the current state of the game (pot and player info)
void PokerGame::printGameState(int curPlayerIndex) const {
    // collect and output pot total
    int pot = 0;
    for (int i = 0; i < players.size(); i++) {
        pot += players[i]->getAmountBet();
    }
    cout << "Total pot: " << pot << endl;

    // output relevant player state info
    for (int i = 0; i < players.size(); i++) {
        Player& player = *players[i];
        // indicate player whose turn it is
        if (i == curPlayerIndex) {
            cout << "-> " << player.getName();
        }
        else {
            cout << "   " << player.getName();
        }

        // only display detailed information if the player was dealt in this round
        if (player.hasHand()) {
            // indicate if player is folded or bankrupt
            if (player.getIsFolded()) {
                cout << " (FOLDED)";
            }
            if (player.getChipCount() <= 0) {
                cout << " (BANKRUPT)";
            }
            cout << endl;
            // output amount bet this round and total chip count
            cout << "Bet:  " << player.getAmountBet() << "/" << player.getChipCount() << endl;
            // output dealt hand
            cout << "Hand: " << player.getHand().toString() << endl;
        }
        else {
            // player was not dealt in this round, so they must be bankrupt
            cout << " (BANKRUPT)" << endl;
        }
    }
}

// initializes the cards in a standard deck (no jokers)
void PokerGame::initDeckTemplate() {
    const std::array<char, 13> cardRanks = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
    const std::array<char, 4> cardSuits = { 'C', 'S', 'H', 'D' };

    for (int i = 0; i < sizeof(cardSuits); ++i) {
        for (int j = 0; j < sizeof(cardRanks); ++j) {
            deckTemplate.push_back(Card(cardRanks[j], cardSuits[i]));
        }
    }
}