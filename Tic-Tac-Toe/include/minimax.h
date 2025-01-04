#include "structures.h"
#include "computer.h"
#include <stdbool.h>
#ifndef MINIMAX_H_INCLUDED
#define MINIMAX_H_INCLUDED

/**
 * @brief Minimax algorithm for determining the best possible move in a given game state. The minimax algorithm recursively explores all possible moves up to a fixed depth.
 *
 * @param gameSettings A pointer to the game settings containing the current game state.
 * @param depth The current depth of the recursion.
 * @param computerTurn A bool indicating whether it is the computer's turn to move or not.
 * @param alpha The current alpha value for alpha-beta pruning.
 * @param beta The current beta value for alpha-beta pruning.
 * @param maxDepth The maximum search depth for the minimax algorithm.
 * @return The best score for the current game state.
 */
int minimax(GameSettings* gameSettings, int depth, bool computerTurn, int alpha, int beta, int maxDepth);

int heuristicEvaluation(GameSettings* gameSettings, bool computerTurn);


/**
 * @brief Heuristic function to evaluate the score of a streak in a given direction (row col, RLD, LRD).
 *
 * @param gameSettings A pointer to the game settings containing the current game state.
 * @param startRow The starting row index of the streak.
 * @param startCol The starting column index of the streak.
 * @param streakType The type of the streak .
 * @param computerTurn A boolean indicating whether it is the computer's turn to move.
 * @return The heuristic score for the streak.
 */
int heuristicScore(GameSettings* gameSettings, int startRow, int startCol, StreakType streakType,bool computerTurn);

/**
 * @brief Calculates the score for a particular streak based on the number of player and computer symbols and open ends.
 *
 *
 * @param playerSymbolCnt The number of X symbols in the streak.
 * @param computerSymbolCnt The number of O symbols in the streak.
 * @param openEnds The number of open ends in the streak.
 * @param computerTurn A boolean indicating whether it is the computer's turn.
 * @return The calculated score for the streak.
 */
int calculateScore(int playerSymbolCnt, int computerSymbolCnt, int openEnds, bool computerTurn);

/**
 * @brief Checks if a specific position/cell is worth trying for a move based on its neighboring cells.
 *
 * @param gameSettings A pointer to the game settings containing the current game state.
 * @param row The row index of the cell to check.
 * @param col The column index of the cell to check.
 * @return true if the cell has neighbors for any direction, false otherwise.
 */
bool isWorthTrying(GameSettings* gameSettings, int row, int col);

/**
 * @brief Finds the best possible move for the computer using the minimax algorithm.
 *
 * @param gameSettings A pointer to the game settings containing the current game state.
 * @param maxDepth The maximum depth for the minimax search.
 * @return The best position for the computer's move.
 */
Position findBestMove(GameSettings *gameSettings, int maxDepth);


#endif // MINIMAX_H_INCLUDED
