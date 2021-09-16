/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #3: Tic Tac Toe
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/19/2021
 * Description: This program provides some automated test cases for TicTacToe.cpp.
 **/

#include <iostream>
#include "TicTacToe.h"
using namespace std;

int main()
{
    // Instance of statistic that will be used for testing
    TicTacToe ticTacToe;

    ticTacToe.makeUserMove(1, 3);
    ticTacToe.makeUserMove(3, 1);

    return 0;
}