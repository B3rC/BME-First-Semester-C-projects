#include <stdbool.h>

#include "structures.h"

#ifndef FILEHANDLING_H_INCLUDED
#define FILEHANDLING_H_INCLUDED

/**
 * @brief Saves the current game state to a file.
 *
 * This function writes the game settings and the game map to a file
 * named "savedGame.txt".
 *
 * @param gameSettings Pointer to the current game settings and state.
 * @return `true` if the game was saved successfully, `false` otherwise.
 *
 */
bool saveGame(GameSettings* gameSettings);

/**
 * @brief Initializes game settings from file.
 *
 * This function sets up the initial game settings by copying the map dimensions and difficulty level
 * from a .txt file.
 *
 * @param gameSettings Pointer to the GameSettings structure to initialize.
 */
bool initSettingsFromFile(GameSettings* gameSettings);

#endif // FILEHANDLING_H_INCLUDED
