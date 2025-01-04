/**
 * @file structures.h
 * @brief This header file defines the data structures and enums used in the game.
 *
 * This file contains the following:
 * - Enumerations for game difficulty, next player to move, and game map symbols.
 * - Structures for game settings, positions on the game map, and streaks for win conditions.
 *
 * Dependencies:
 * - SDL2 for color definitions.
 */
#include <SDL2/SDL.h>

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

extern SDL_Color red;
extern SDL_Color white;
extern SDL_Color blue;
extern SDL_Color green;
extern SDL_Color black;
extern SDL_Color beige;
extern SDL_Color light_red;
extern SDL_Color grey;
extern SDL_Color light_green;


typedef enum Difficulty{
    DIFFICULTY_NORMAL, DIFFICULTY_HARD
}Difficulty;

typedef enum NextToMove{
    NEXT_PLAYER, NEXT_COMPUTER, NEXT_NONE
}NextToMove;

typedef enum GameMap{
    SYMBOL_X=1, SYMBOL_CIRCLE=2, SYMBOL_BLANK=0
}GameMap;

typedef struct Position{
    int x,y;
}Position;

/**
 * @brief Structure to hold game settings.
 */
typedef struct GameSettings{
    int mapWidth, mapHeight;
    GameMap **gameMap;
    Difficulty difficulty;
    NextToMove nextToMove;
}GameSettings;

/**
 * @brief Enumeration for the types of streaks.
 */
typedef enum StreakType{
    STREAK_ROW, STREAK_COLUMN, STREAK_RLD, STREAK_LRD
}StreakType;

/**
 * @brief Structure to represent a streak for winning conditions.
 */
typedef struct Streak{
    int streakLength;
    int streak_x, streak_y;
    StreakType streakType;
    Position blockablePos;
}Streak;

/**
 * @brief Structure to represent a rectangle (x,y are coordinates for the center)
 */
typedef struct Rectangle{
    int x, y;
    int w, h;
}Rectangle;



#endif // STRUCTURES_H_INCLUDED
