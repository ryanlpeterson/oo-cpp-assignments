/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #3: Tic Tac Toe
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/19/2021
 * Description: Maintains the state of a tic-tac-toe game. Game is initialized
 *  with an empty board. User (X) makes moves. Computer (O) makes random moves
 *  in response. After each move the board is printed and it is checked
 *  whether the game has ended, either with a win or a tie.
 **/

#include <iostream>
#include "TicTacToe.h"
using namespace std;

/**
 * Default constructor. Initializes instance variables and prints the initial board.
 **/
TicTacToe::TicTacToe() :
    // new game, board is empty and game is not over
    numCellsOccupied (0),
    isGameOver (false)
{
    // intialize board state
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = EMPTY_MARKER;
        }
    }

    // initialize random with a different seed each time by using the current time 
    srand(time(NULL));

    // print the initial empty board state
    printBoard();
}

/**
 * If valid, updates the board with a user move in the given position. Valid rows and columns
 * are 1, 2, or 3, and must be a position not yet occupied by a previous move. Prints the
 * board after the move. Checks if the game is over, and if not has the computer play a move.
 **/
void TicTacToe::makeUserMove(int row, int column)
{
    // check if the given position is within the board dimensions
    if (row < 1 || row > 3 || column < 1 || column > 3)
    {
        cout << "Row and column must be values between 1 and 3. Move not made. Please try again.\n";
        return;
    }

    // adjust given values to align with the board matrix
    row--;
    column--;

    // check if the given position is already occupied
    if (board[row][column] != EMPTY_MARKER)
    {
        cout << "Selected cell is already occupied. Move not made. Please try again.\n";
        return;
    }

    // move selection was valid, so update the board state
    board[row][column] = USER_MARKER;
    numCellsOccupied++;

    printBoard();

    checkGameOver();

    if (!isGameOver)
    {
        // game is not over, so have the computer play a move
        makeComputerMove();
    }
}

/**
 * Returns whether the game has been determined as over
 **/
bool TicTacToe::getIsGameOver()
{
    return isGameOver;
}

/**
 * Updates the board with a random valid computer move. Prints the board after the move.
 * Checks if the game is over.
 **/
void TicTacToe::makeComputerMove()
{
    // based on the number of empty cells, select one for the computer's move
    int numCellsEmpty = NUM_BOARD_CELLS - numCellsOccupied;
    int selectedEmptyCell = rand() % numCellsEmpty;

    // iterate through the board, until the selected empty cell is found
    // skip occupied cells
    int emptyCellCursor = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY_MARKER)
            {
                // cell is empty, determine if it is the selected empty cell
                if (emptyCellCursor == selectedEmptyCell)
                {
                    // arrived, make the computer's move at this position
                    // update the board state
                    board[i][j] = COMPUTER_MARKER;
                    numCellsOccupied++;

                    printBoard();

                    checkGameOver();

                    // break early
                    // guaranteed to get here because there will always be an empty
                    // cell when this function is called
                    return;
                }
                // did not yet arrive at the selected empty cell
                emptyCellCursor++;
            }
        }
    }
}

/**
 * Determine whether the game is over, either by win or tie. Print any game over
 * message and update the isGameOver state.
 **/
void TicTacToe::checkGameOver()
{
    if (isWinner(USER_MARKER))
    {
        // user won
        cout << "GAME OVER: " << USER_MARKER << " wins!\n";
        isGameOver = true;
    }
    else if (isWinner(COMPUTER_MARKER))
    {
        // computer won
        cout << "GAME OVER: " << COMPUTER_MARKER << " wins!\n";
        isGameOver = true;
    }
    else if (isTie())
    {
        // tie
        cout << "GAME OVER: TIE\n";
        isGameOver = true;
    }
}

/**
 * Determine if the given player has won.
 **/
bool TicTacToe::isWinner(char playerMarker)
{
    // need to check if any row, column, or diagonal is completely full with the given playerMarker

    // check rows
    for (int i = 0; i < 3; i++)
    {
        // assume all matches and be proven otherwise
        bool allMatches = true;
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != playerMarker)
            {
                // non-player marker found in the row
                allMatches = false;
                // break out of the inner loop to get to the next row
                break;
            }
        }
        if (allMatches)
        {
            return true;
        }
    }
    // check columns
    // flip the nested loop order of i and j to check the columns
    for (int j = 0; j < 3; j++)
    {
        // assume all matches and be proven otherwise
        bool allMatches = true;
        for (int i = 0; i < 3; i++)
        {
            if (board[i][j] != playerMarker)
            {
                // non-player marker found in the column
                allMatches = false;
                // break out of the inner loop to get to the next column
                break;
            }
        }
        if (allMatches)
        {
            return true;
        }
    }

    // check diagonals
    // could do something smarter here if there was a concern of the board dimensions changing
    // e.g. loop with some basic arithmetic to iterate down the diagonals
    if ((board[0][0] == playerMarker && board[1][1] == playerMarker && board[2][2] == playerMarker) ||
        (board[0][2] == playerMarker && board[1][1] == playerMarker && board[2][0] == playerMarker))
    {
        return true;
    }

    return false;
}

/**
 * Determine if the game has ended in a tie.
 **/
bool TicTacToe::isTie()
{
    // tie if all cells are occupied
    return numCellsOccupied >= NUM_BOARD_CELLS;
}

/**
 * Print the board in a nice format.
 **/
void TicTacToe::printBoard()
{
    // could do something smarter here if there was a concern of the board dimensions changing
    // e.g. nested loop with checks to only print the dividing lines between the appropriate rows and columns
    cout << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
    cout << "-----" << endl;
    cout << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
    cout << "-----" << endl;
    cout << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << endl;
    cout << "============" << endl;
}