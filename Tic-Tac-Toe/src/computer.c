#include "computer.h"

#include "check.h"

#include <stdio.h>

#include <time.h>

#include <limits.h>

#include "minimax.h"


void makeNormalModeMove(GameSettings * gameSettings) {

  Position bestPos = findBestMove(gameSettings, 2);
  if (isLegitMove(bestPos.x, bestPos.y, gameSettings)) {
    makeMove(bestPos.x, bestPos.y, gameSettings, SYMBOL_CIRCLE);
  } else {
    makeRandomMove(gameSettings);
  }
  return;

}

void makeHardModeMove(GameSettings * gameSettings) {
  Position bestPos = findBestMove(gameSettings, 4);
  if (isLegitMove(bestPos.x, bestPos.y, gameSettings)) {
    makeMove(bestPos.x, bestPos.y, gameSettings, SYMBOL_CIRCLE);
  } else {
    makeRandomMove(gameSettings);
  }
  return;
}

void makeRandomMove(GameSettings * gameSettings) {
  srand(time(NULL));

  int x = (rand() % gameSettings -> mapWidth);
  int y = (rand() % gameSettings -> mapHeight);

  while (!isLegitMove(x, y, gameSettings)) {
    x = (rand() % gameSettings -> mapWidth);
    y = (rand() % gameSettings -> mapHeight);

  }
  gameSettings -> gameMap[x][y] = SYMBOL_CIRCLE;

}

void makeMove(int x, int y, GameSettings * gameSettings, GameMap symbol) {

  gameSettings -> gameMap[x][y] = symbol;
}

void undoMove(int x, int y, GameSettings * gameSettings) {

  gameSettings -> gameMap[x][y] = SYMBOL_BLANK;
}
