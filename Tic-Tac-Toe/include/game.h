#include "structures.h"
#include <stdbool.h>
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

void Game(GameSettings gameSettings, bool loadFromFile);

/**
 * @brief Frees the allocated memory for the game map.
 *
 *
 * @param gameSettings Pointer to the GameSettings structure containing the game map to free.
 */
void GameMap_Memory_Free(GameSettings* gameSettings);

/**
 * @brief Handles the player's move based on the mouse position.
 *
 * This function calculates the grid cell position based on the mouse position and
 * sets the selected cell to the player symbol.
 *
 * @param gameSettings Pointer to the GameSettings structure containing the game state.
 * @param mousePos SDL_Point structure with the mouse coordinates.
 * @param cellSize The size of a cell in the game map.
 */
void makePlayerMove(GameSettings* gameSettings, SDL_Point mousePos, int cellSize);

/**
 * @brief Executes the computer's move based on the selected difficulty level.
 *
 * @param gameSettings Pointer to the GameSettings structure containing the game state.
 */
void makeComputerMove(GameSettings* gameSettings);

/**
 * @brief Allocates memory and initializes the game map.
 *
 * This function allocates memory for a 2D game map array based on the specified height and width
 * in the game settings. It also initializes each cell in the map to a blank state.
 * It's the caller's responsibility to free the allocated memory. Use GameMap_Memory_Free for that.
 *
 * @param gameSettings Pointer to the GameSettings structure.
 * @return true if memory allocation and initialization are successful, false otherwise.
 */
bool GameMap_Init(GameSettings* gameSettings);

#endif // GAME_H_INCLUDED
