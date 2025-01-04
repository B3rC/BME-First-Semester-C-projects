#include "structures.h"
#include <stdbool.h>
#ifndef COMPUTER_H_INCLUDED
#define COMPUTER_H_INCLUDED

/**
 * @brief Makes a normal difficulty mode for the computer by finding the best move
 *        based on a depth-limited minimax seach (depth of 2).
 *
 * @param gameSettings Pointer to the GameSettings structure containing the game state.
 */
void makeNormalModeMove(GameSettings* gameSettings);

/**
 * @brief Makes a hard difficulty mode for the computer by finding the best move
 *        based on a depth-limited minimax seach (depth of 3/4).
 *
 * @param gameSettings Pointer to the GameSettings structure containing the game state.
 */
void makeHardModeMove(GameSettings* gameSettings);

/**
 * @brief Makes a random move for the computer by placing the symbol at a random
 *        BLANK position.

 * @param gameSettings pointer to the GameSettings structure containing the game state.
 */
void makeRandomMove(GameSettings* gameSettings);

/**
 * @brief Places a specified symbol on the game map at a given position.
 *
 * This function sets the cell at (x, y) on the game map to the specified symbol.
 *
 * @param x The x-coordinate of the position on the game map.
 * @param y The y-coordinate of the position on the game map.
 * @param gameSettings Pointer to the GameSettings structure containing the game state.
 * @param symbol The symbol to be placed
 */
void makeMove(int x, int y, GameSettings* gameSettings, GameMap symbol);

/**
 * @brief Undoes a move by setting the specified position back to blank.
 *
 * @param x The x coordinate of the position on the game map.
 * @param y The y coordinate of the position on the game map.
 * @param gameSettings Pointer to the GameSettings structure containing the game state.
 */
void undoMove(int x, int y, GameSettings* gameSettings);

#endif // COMPUTER_H_INCLUDED
