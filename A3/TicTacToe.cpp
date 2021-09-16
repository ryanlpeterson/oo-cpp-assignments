/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #3: Tic Tac Toe
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/19/2021
 * Description: 
 **/

#include <iostream>
#include "TicTacToe.h"
using namespace std;

/**
 * Default constructor. Initializes instance variables.
 **/
TicTacToe::TicTacToe() :
    numCellsOccupied (0)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = EMPTY_MARKER;
        }
    }
    printBoard();
}

void TicTacToe::makeUserMove(int row, int column)
{
    if (row < 1 || row > 3 || column < 1 || column > 3)
    {
        cout << "Row and column must be values between 1 and 3. Move not made. Please try again.";
        return;
    }

    // adjust given values to align with matrix
    row--;
    column--;

    if (board[row][column] != EMPTY_MARKER)
    {
        cout << "Selected cell is already occupied. Move not made. Please try again.";
        return;
    }

    board[row][column] = USER_MARKER;
    numCellsOccupied++;

    printBoard();

    checkGameOver();

    makeComputerMove();
}

void TicTacToe::makeComputerMove()
{
    int numCellsEmpty = NUM_BOARD_CELLS - numCellsOccupied;

    int selectedEmptyCell = rand() % numCellsEmpty;

    int emptyCellCursor = 0;
    // TODO: update this to break early
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY_MARKER)
            {
                if (emptyCellCursor == selectedEmptyCell)
                {
                    board[i][j] = COMPUTER_MARKER;
                    numCellsOccupied++;
                }
                emptyCellCursor++;
            }
        }
    }

    printBoard();

    checkGameOver();
}

void TicTacToe::checkGameOver()
{
    if (isWinner(USER_MARKER))
    {
        cout << "GAME OVER: " << USER_MARKER << " wins!";
    }
    else if (isWinner(COMPUTER_MARKER))
    {
        cout << "GAME OVER: " << COMPUTER_MARKER << " wins!";
    }
    else if (isTie())
    {
        cout << "GAME OVER: TIE";
    }
}

bool TicTacToe::isWinner(char playerMarker)
{
    // ...
    return false;
}

bool TicTacToe::isTie()
{
    return numCellsOccupied >= NUM_BOARD_CELLS;
}

void TicTacToe::printBoard()
{
    cout << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
    cout << "-----" << endl;
    cout << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
    cout << "-----" << endl;
    cout << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << endl;
    cout << "============" << endl;
}