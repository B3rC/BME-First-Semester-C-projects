#include "filehandling.h"
#include <stdlib.h>
#include <stdio.h>
#include "game.h"

bool initSettingsFromFile(GameSettings * gameSettings) {

  FILE * fp = fopen("savedGame.txt", "r");
  if (fp == NULL) {
    perror("Unable to open file");
    return false;
  }

  // Buffer to skip lines
  char buffer[20];

  // #MapSize
  if (!fgets(buffer, sizeof(buffer), fp) ||
    fscanf(fp, "%dx%d\n", & gameSettings -> mapHeight, & gameSettings -> mapWidth) != 2) {
    fclose(fp);
    perror("Failed to read map size");
    return false;
  }

  // Initialize GameMap based on height and width
  if (!GameMap_Init(gameSettings)) {
    fclose(fp);
    return false;
  }

  // #GameState
  if (!fgets(buffer, sizeof(buffer), fp)) {
    fclose(fp);
    perror("Failed to read text #GameState");
    return false;
  }

  int value;
  for (int i = 0; i < gameSettings -> mapHeight; i++) {
    for (int j = 0; j < gameSettings -> mapWidth; j++) {
      if (fscanf(fp, "%d ", & value) != 1) {
        fclose(fp);
        perror("Failed to read GameState values");
        return false;
      }
      gameSettings -> gameMap[i][j] = (value == 1) ? SYMBOL_X : (value == 2) ? SYMBOL_CIRCLE : SYMBOL_BLANK;
    }
  }

  // #NextToMove
  if (!fgets(buffer, sizeof(buffer), fp) ||
    fscanf(fp, "%d\n", & value) != 1) {
    fclose(fp);
    perror("Failed to read next to move");
    return false;
  }
  gameSettings -> nextToMove = (value == 0) ? NEXT_PLAYER : NEXT_COMPUTER;

  // #Difficulty
  if (!fgets(buffer, sizeof(buffer), fp) ||
    fscanf(fp, "%d\n", & value) != 1) {
    fclose(fp);
    perror("Failed to read difficulty level");
    return false;
  }
  gameSettings -> difficulty = (value == 0) ? DIFFICULTY_NORMAL : DIFFICULTY_HARD;

  fclose(fp);
  return true;
}

bool saveGame(GameSettings * gameSettings) {
  FILE * fp = fopen("savedGame.txt", "w");
  if (fp == NULL) {
    perror("Unable to open file");
    return false;
  }

  // Save map height , width
  if (fprintf(fp, "#MapSize\n") < 0 ||
    fprintf(fp, "%dx%d\n", gameSettings -> mapHeight, gameSettings -> mapWidth) < 0) {
    fclose(fp);
    perror("Failed to write map size");
    return false;
  }

  // Save game state
  if (fprintf(fp, "#GameState\n") < 0) {
    fclose(fp);
    perror("Failed to write game state header");
    return false;
  }

  for (int i = 0; i < gameSettings -> mapHeight; i++) {
    for (int j = 0; j < gameSettings -> mapWidth; j++) {
      if (fprintf(fp, "%d ", gameSettings -> gameMap[i][j]) < 0) {
        fclose(fp);
        perror("Failed to write game state values");
        return false;
      }
    }
    if (fprintf(fp, "\n") < 0) {
      fclose(fp);
      perror("Failed to write new line");
      return false;
    }
  }

  // Save next to move
  if (fprintf(fp, "#NextToMove\n") < 0 ||
    fprintf(fp, "%d\n", gameSettings -> nextToMove == NEXT_PLAYER ? 0 : 1) < 0) {
    fclose(fp);
    perror("Failed to write next to move");
    return false;
  }

  // Save difficulty level
  if (fprintf(fp, "#Difficulty\n") < 0 ||
    fprintf(fp, "%d\n", gameSettings -> difficulty == DIFFICULTY_NORMAL ? 0 : 1) < 0) {
    fclose(fp);
    perror("Failed to write difficulty level");
    return false;
  }

  fclose(fp);
  return true;
}
