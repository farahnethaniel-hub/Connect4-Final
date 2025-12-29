#include <stdio.h>
#include "logic.h"
#include <stdlib.h>
#include <time.h>
/* Hard AI: Advanced strategy including center control and move validation */
int getComputerMoveHard(char board[ROWS][COLS], char computerPlayer) {
    char humanPlayer = (computerPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    int col;
    // 1. Priority 1: Check if computer can win now
    for (col = 0; col < COLS; col++) {
        if (board[0][col] == EMPTY) {
            int row;
            for (row = ROWS - 1; row >= 0; row--) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = computerPlayer;
                    if (checkWin(board, computerPlayer)) {
                        board[row][col] = EMPTY;
                        return col;
                    }
                    board[row][col] = EMPTY;
                    break;
                }
            }
        }
    }
    // 2. Priority 2: Block human's immediate win
    for (col = 0; col < COLS; col++) {
        if (board[0][col] == EMPTY) {
            int row;
            for (row = ROWS - 1; row >= 0; row--) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = humanPlayer;
                    if (checkWin(board, humanPlayer)) {
                        board[row][col] = EMPTY;
                        return col;
                    }
                    board[row][col] = EMPTY;
                    break;
                }
            }
        }
    }

    // 3. Priority 3: Strategic center control (Column 3 is the most valuable)
    if (board[0][3] == EMPTY) {
        // Only take the center if it doesn't set up a win for the human
        return 3;
    }
    // 4. Fallback: Use Smart logic
    return getComputerMoveSmart(board, computerPlayer);
}

/* Medium AI: Tries to win or block the player, otherwise moves randomly */
int getComputerMoveSmart(char board[ROWS][COLS], char computerPlayer) {
    char humanPlayer = (computerPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    int col;

    // 1. Check if the computer can win in the next move
    for (col = 0; col < COLS; col++) {
        if (board[0][col] == EMPTY) { // Only check if column is not full
            // Simulate the move
            int row;
            for (row = ROWS - 1; row >= 0; row--) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = computerPlayer;
                    if (checkWin(board, computerPlayer)) {
                        board[row][col] = EMPTY; // Undo move
                        return col; // Found winning move!
                    }
                    board[row][col] = EMPTY; // Undo move
                    break;
                }
            }
        }
    }

    // 2. Check if the human can win in their next move and block them
    for (col = 0; col < COLS; col++) {
        if (board[0][col] == EMPTY) {
            int row;
            for (row = ROWS - 1; row >= 0; row--) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = humanPlayer;
                    if (checkWin(board, humanPlayer)) {
                        board[row][col] = EMPTY; // Undo move
                        return col; // Block human win!
                    }
                    board[row][col] = EMPTY; // Undo move
                    break;
                }
            }
        }
    }

    // 3. Otherwise, pick a random available column
    return getComputerMoveEasy(board);
}

/* Easy AI: Picks a random valid column */
int getComputerMoveEasy(char board[ROWS][COLS]) {
    int col;
    // Keep picking a random column until we find one that isn't full
    do {
        col = rand() % COLS; // Generates a number between 0 and 6
    } while (board[0][col] != EMPTY);

    return col;
}
/* Initializes the game board with empty spaces */
void initBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = EMPTY;
        }
    }
}
/* Prints the board with a simple ASCII interface */
void printBoard(char board[ROWS][COLS]) {
    printf("\n  1 2 3 4 5 6 7\n"); // Column headers for the user
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
    printf("---------------\n");
}

/* Attempts to drop a piece into a column. Returns 1 if successful, 0 otherwise */
int makeMove(char board[ROWS][COLS], int col, char player) {
    // Check if the column index is within the valid array range [0-6]
    if (col < 0 || col >= COLS) {
        return 0;
    }

    // Search from the bottom row up to find the first empty spot
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == EMPTY) {
            board[i][col] = player;
            return 1; // Move executed
        }
    }
    return 0; // Column is already full
}

/* Checks if the given player has won the game */
int checkWin(char board[ROWS][COLS], char player) {
    // 1. Horizontal check (Rows)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i][j + 1] == player &&
                board[i][j + 2] == player && board[i][j + 3] == player)
                return 1;
        }
    }
    // 2. Vertical check (Columns)
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == player && board[i + 1][j] == player &&
                board[i + 2][j] == player && board[i + 3][j] == player)
                return 1;
        }
    }
    // 3. Diagonal check (Down-Right \)
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i + 1][j + 1] == player &&
                board[i + 2][j + 2] == player && board[i + 3][j + 3] == player)
                return 1;
        }
    }
    // 4. Diagonal check (Up-Right /)
    for (int i = 3; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i - 1][j + 1] == player &&
                board[i - 2][j + 2] == player && board[i - 3][j + 3] == player)
                return 1;
        }
    }
    return 0; // No win detected
}
/* Returns 1 if no more moves can be made, 0 otherwise */
int isBoardFull(char board[ROWS][COLS]) {
    for (int j = 0; j < COLS; j++) {
        // If any top-row cell is empty, the board is not full
        if (board[0][j] == EMPTY) return 0;
    }
    return 1;
}