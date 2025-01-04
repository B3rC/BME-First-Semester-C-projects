#include "check.h"

#include <stdio.h>

bool isInRectangle(SDL_Point point, int x, int y, int w, int h) {
  return point.x >= (x - w / 2) && point.y >= (y - h / 2) && point.x <= (x + w / 2) && point.y <= (y + h / 2) ? true : false;
}

bool isInGameArea(SDL_Point point, int x1, int y1, int x2, int y2) {
  return point.x >= x1 && point.y >= y1 && point.x <= x2 && point.y <= y2 ? true : false;
}

bool isLegitMove(int row, int column, GameSettings * settings) {
  if ((row < settings -> mapHeight && column < settings -> mapWidth) && row >= 0 && column >= 0) {
    if (settings -> gameMap[row][column] == SYMBOL_BLANK) {
      return true;
    } else return false;
  } else return false;
}

bool checkWin(GameSettings * settings, GameMap checkForSymbol) {
  // row
  for (int i = 0; i < settings -> mapHeight; i++) {
    int streak = 0;
    for (int j = 0; j < settings -> mapWidth; j++) {
      if (settings -> gameMap[i][j] == checkForSymbol) {
        streak++;
        if (streak >= 5) {

          return true;
        }
      } else {
        streak = 0;
      }
    }
  }

  // column
  for (int i = 0; i < settings -> mapWidth; i++) {
    int streak = 0;
    for (int j = 0; j < settings -> mapHeight; j++) {
      if (settings -> gameMap[j][i] == checkForSymbol) {
        streak++;
        if (streak >= 5) {
          return true;
        }
      } else {
        streak = 0;
      }
    }
  }

  // RLD
  for (int i = 0; i < settings -> mapHeight; i++) {
    for (int j = 0; j < settings -> mapWidth; j++) {
      if (i + 4 < settings -> mapHeight && j - 4 >= 0) {
        int streak = 0;
        for (int k = 0; k < 5; k++) {
          if (settings -> gameMap[i + k][j - k] == checkForSymbol) {
            streak++;
          } else {
            break;
          }
        }
        if (streak >= 5) {

          return true;
        }
      }
    }
  }

  // LRD
  for (int i = 0; i < settings -> mapHeight; i++) {
    for (int j = 0; j < settings -> mapWidth; j++) {
      if (i + 4 < settings -> mapHeight && j + 4 < settings -> mapWidth) {
        int streak = 0;
        for (int k = 0; k < 5; k++) {
          if (settings -> gameMap[i + k][j + k] == checkForSymbol) {
            streak++;
          } else {
            break;
          }
        }
        if (streak >= 5) {

          return true;
        }
      }
    }
  }
  return false;
}

bool isBoardFull(GameSettings * settings) {
  for (int i = 0; i < settings -> mapHeight; i++) {
    for (int j = 0; j < settings -> mapWidth; j++) {
      if (settings -> gameMap[i][j] == SYMBOL_BLANK) {
        return false;
      }
    }
  }
  return true;
}
