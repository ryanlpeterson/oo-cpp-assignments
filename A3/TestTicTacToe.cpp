/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #3: Tic Tac Toe
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/19/2021
 * Description: This program provides an interactive test interface for TicTacToe.cpp.
 **/

#include <iostream>
#include "TicTacToe.h"
using namespace std;

int main()
{
    // Instance of TicTacToe that will be used for testing
    TicTacToe ticTacToe;

    int row;
    int column;
    while (!ticTacToe.getIsGameOver())
    {
        cout << "Select Row: ";
        cin >> row;
        cout << "Select Column: ";
        cin >> column;

        ticTacToe.makeUserMove(row, column);
    }

    return 0;
}