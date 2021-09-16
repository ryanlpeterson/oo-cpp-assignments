/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #3: Tic Tac Toe
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/19/2021
 **/

class TicTacToe
{
    public:
        // default ctor
        TicTacToe();

        void makeUserMove(int row, int column);

    private:
        void makeComputerMove();

        void checkGameOver();

        bool isWinner(char playerMarker);

        bool isTie();

        void printBoard();


        int numCellsOccupied;

        char board[3][3];

        static const char USER_MARKER = 'X';
        static const char COMPUTER_MARKER = 'O';
        static const char EMPTY_MARKER = ' ';

        static const int NUM_BOARD_CELLS = 9;
};