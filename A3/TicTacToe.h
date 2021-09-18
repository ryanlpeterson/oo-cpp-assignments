/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #3: Tic Tac Toe
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/19/2021
 **/

class TicTacToe
{
    public:
        // default ctor, initializes a new game
        TicTacToe();

        // if valid, update the board with the given user move
        void makeUserMove(int row, int column);

        // get whether the game is over, either by win or tie
        bool getIsGameOver();

    private:
        // private member functions
        // update the board with a computer move
        void makeComputerMove();

        // determine whether the game is over, either by win or tie
        void checkGameOver();

        // determine if the given player has won
        bool isWinner(char playerMarker);

        // determine whether the game has ended in a tie
        bool isTie();

        // print the board to the console
        void printBoard();


        // private instance variables
        // number of cells occupied by player moves
        int numCellsOccupied;
        // boolean indicated whether the game has ended
        bool isGameOver;
        // matrix representing the board state through characters
        char board[3][3];

        // private constants
        // the character representing the user on the board
        static const char USER_MARKER = 'X';
        // the character representing the computer on the board
        static const char COMPUTER_MARKER = 'O';
        // the character representing that a board cell is empty
        static const char EMPTY_MARKER = ' ';
        // total number of cells on the 3x3 board
        static const int NUM_BOARD_CELLS = 9;
};