/**
 * @file check.h
 * @brief This header file contains function declarations for various checks and validations
 *        used in the game.
 *
 * This file includes the following functionalities:
 * - Functions to check if a point is within a rectangle or a specific game area.
 * - Validation of moves to ensure they are legitimate according to the game rules.
 * - Functions to find and analyze streaks of symbols on the game board, including
 *   checking for diagonal streaks and finding blocking positions.
 *
 * This header should be included in the implementation files that require these checks
 * to manage the game logic effectively.
 *
 * Dependencies:
 * - SDL2 for handling graphical points and coordinates.
 * - structures.h for data structures and enums related to game settings and symbols.
 */
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "structures.h"

#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED


bool isInRectangle(SDL_Point point, int x, int y, int w, int h);

/**
 * @brief Checks if there is a winning streak of 5 consecutive symbols in any row, column,
 *        or diagonal for the given symbol.
 *
 * @param settings Pointer to the GameSettings structure containing the game state.
 * @param checkForSymbol The symbol (X or O) to check for a winning streak.
 * @return true if there is a winning streak of 5 consecutive symbols, false otherwise.
 */
bool checkWin(GameSettings *settings, GameMap checkForSymbol);

bool isInGameArea(SDL_Point point,int x1, int y1, int x2, int y2);

/**
 * @brief Checks if the specified move is valid.
 *
 * This function determines whether a move to the specified row and column
 * is legit based on the game settings.
 *
 * @param row The row index of the move to check.
 * @param column The column index of the move to check.
 * @param settings A pointer to the GameSettings structure containing the current game state.
 * @return true if the move is valid, false otherwise.
 */
bool isLegitMove(int row, int column, GameSettings* settings);

/**
 * @brief Checks if the game board is completely filled with symbols.
 *
 * @param settings Pointer to the GameSettings structure containing the game state.
 * @return true if the board is full, false otherwise.
 */
bool isBoardFull(GameSettings *settings);

#endif // CHECK_H_INCLUDED
