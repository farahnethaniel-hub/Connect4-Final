#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logic.h"

/* * Function to handle the Player vs Player game mode.
 * Returns: 1 if Player 1 wins, 2 if Player 2 wins, 0 for a draw.
 */
int playPvP(char board[ROWS][COLS], char name1[], char name2[]) {
    char currentPlayerChar = PLAYER1;
    char* currentPlayerName = name1;
    int userCol, internalCol;
    int gameRunning = 1;

    initBoard(board);
    printBoard(board);

    while (gameRunning) {
        printf("\n%s, enter column (1-7): ", currentPlayerName);

        if (scanf("%d", &userCol) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        internalCol = userCol - 1;

        if (makeMove(board, internalCol, currentPlayerChar)) {
            printBoard(board);

            if (checkWin(board, currentPlayerChar)) {
                printf("\nCongratulations! %s wins!\n", currentPlayerName);
                return (currentPlayerChar == PLAYER1) ? 1 : 2;
            }

            if (isBoardFull(board)) {
                printf("\nThe board is full! It's a draw.\n");
                return 0;
            }

            // Switch players
            if (currentPlayerChar == PLAYER1) {
                currentPlayerChar = PLAYER2;
                currentPlayerName = name2;
            }
            else {
                currentPlayerChar = PLAYER1;
                currentPlayerName = name1;
            }
        }
        else {
            printf("Invalid move! Column full or out of bounds. Try again.\n");
        }
    }
    return 0;
}

/* * Function to handle the Player vs Computer game mode.
 * Returns: 1 if Player wins, 2 if Computer wins, 0 for a draw.
 */
int playPvC(char board[ROWS][COLS], char playerName[]) {
    char playerChar = PLAYER1;
    char computerChar = PLAYER2;
    int userCol, internalCol, difficulty;

    printf("\nChoose AI Difficulty:\n1. Easy\n2. Medium\n3. Hard\nEnter choice: ");
    if (scanf("%d", &difficulty) != 1) {
        difficulty = 1;
        while (getchar() != '\n');
    }

    initBoard(board);
    printBoard(board);

    while (1) {
        // --- Player's Turn ---
        printf("\n%s, enter column (1-7): ", playerName);
        if (scanf("%d", &userCol) != 1) {
            while (getchar() != '\n');
            continue;
        }
        internalCol = userCol - 1;

        if (makeMove(board, internalCol, playerChar)) {
            printBoard(board);

            if (checkWin(board, playerChar)) {
                printf("\nAmazing! %s wins against the computer!\n", playerName);
                return 1; // Player wins
            }
            if (isBoardFull(board)) return 0;

            // --- Computer's Turn ---
            printf("\nComputer is thinking...\n");
            int compCol;
            if (difficulty == 3) compCol = getComputerMoveHard(board, computerChar);
            else if (difficulty == 2) compCol = getComputerMoveSmart(board, computerChar);
            else compCol = getComputerMoveEasy(board);

            makeMove(board, compCol, computerChar);
            printf("Computer placed in column %d.\n", compCol + 1);
            printBoard(board);

            if (checkWin(board, computerChar)) {
                printf("\nComputer wins! Better luck next time.\n");
                return 2; // Computer wins
            }
            if (isBoardFull(board)) return 0;
        }
        else {
            printf("Invalid move! Try again.\n");
        }
    }
}

int main() {
    char board[ROWS][COLS];
    char p1Name[20], p2Name[20];
    int choice, result;

    // Statistics counters [cite: 26]
    int p1Wins = 0, p2Wins = 0, compWins = 0, draws = 0;

    srand((unsigned int)time(NULL)); // Seed for random moves

    do {
        printf("\n======= CONNECT FOUR =======\n");
        printf("1. Player vs Player\n");
        printf("2. Player vs Computer\n");
        printf("3. View Statistics\n");
        printf("4. Exit\n");
        printf("============================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            printf("Enter Player 1 Name: "); scanf("%s", p1Name);
            printf("Enter Player 2 Name: "); scanf("%s", p2Name);
            result = playPvP(board, p1Name, p2Name);
            if (result == 1) p1Wins++;
            else if (result == 2) p2Wins++;
            else draws++;
            break;

        case 2:
            printf("Enter your name: "); scanf("%s", p1Name);
            result = playPvC(board, p1Name);
            if (result == 1) p1Wins++;
            else if (result == 2) compWins++;
            else draws++;
            break;

        case 3:
            printf("\n--- Game Statistics ---\n");
            printf("Player 1 Wins: %d\n", p1Wins);
            printf("Player 2 Wins: %d\n", p2Wins);
            printf("Computer Wins: %d\n", compWins);
            printf("Total Draws:   %d\n", draws);
            printf("-----------------------\n");
            break;

        case 4:
            printf("Exiting... Goodbye!\n");
            break;

        default:
            printf("Invalid selection. Please choose 1-4.\n");
        }
    } while (choice != 4);

    return 0;
}