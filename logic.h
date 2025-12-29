#ifndef LOGIC_H
#define LOGIC_H
/* Constants for the game board */
#define ROWS 6
#define COLS 7
#define EMPTY ' '
#define PLAYER1 'X'
#define PLAYER2 'O'
/* Function Prototypes */
int playPvP(char board[ROWS][COLS], char name1[], char name2[]);
int playPvC(char board[ROWS][COLS], char playerName[]);
int getComputerMoveHard(char board[ROWS][COLS], char computerPlayer);
int getComputerMoveSmart(char board[ROWS][COLS], char computerPlayer);
int getComputerMoveEasy(char board[ROWS][COLS]);

// Initializes the board with EMPTY characters
void initBoard(char board[ROWS][COLS]);

// Displays the board to the console
void printBoard(char board[ROWS][COLS]);

// Handles dropping a piece into a column. Returns 1 if success, 0 if fail.
int makeMove(char board[ROWS][COLS], int col, char player);

// Checks if the specified player has four in a row
int checkWin(char board[ROWS][COLS], char player);

// Checks if the board is completely full (Draw)
int isBoardFull(char board[ROWS][COLS]);
#endif