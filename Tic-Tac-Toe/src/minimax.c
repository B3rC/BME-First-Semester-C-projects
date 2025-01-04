#include "minimax.h"

#include "check.h"

#include <stdio.h>

#include "creategraphic.h"

#include "main.h"

#include "game.h"

#include <limits.h>

#define max(a, b)((a) > (b) ? (a) : (b))
#define min(a, b)((a) < (b) ? (a) : (b))

bool isWorthTrying(GameSettings * gameSettings, int row, int col) {
  if (!isLegitMove(row, col, gameSettings)) return false;

  // Check all directions for neighbors
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;

      int newRow = row + i;
      int newCol = col + j;

      if (newRow >= 0 && newRow < gameSettings -> mapHeight &&
        newCol >= 0 && newCol < gameSettings -> mapWidth) {
        if (gameSettings -> gameMap[newRow][newCol] != SYMBOL_BLANK) {
          return true;
        }
      }
    }
  }

  return false;
}

int calculateScore(int playerSymbolCnt, int computerSymbolCnt, int openEnds, bool computerTurn) {

  if (computerSymbolCnt >= 5) return INT_MAX;
  if (playerSymbolCnt >= 5) return -INT_MAX;

  if (computerTurn) {
    if (computerSymbolCnt == 4 && playerSymbolCnt == 0) {
      return openEnds >= 1 ? 500000 : 50000;
    }
    if (playerSymbolCnt == 4 && computerSymbolCnt == 0) {
      return openEnds >= 1 ? -1000000 : -1000000;
    }
    if (computerSymbolCnt == 3 && playerSymbolCnt == 0) {
      return openEnds >= 2 ? 25000 : 2500;
    }
    if (playerSymbolCnt == 3 && computerSymbolCnt == 0) {
      return openEnds >= 2 ? -50000 : -5000;

    }
  } else {
    if (computerSymbolCnt == 4 && playerSymbolCnt == 0) {
      return openEnds >= 2 ? 1000000 : -100000;
    }
    if (playerSymbolCnt == 4 && computerSymbolCnt == 0) {
      return openEnds >= 2 ? -1000000 : -100000;
    }
    if (playerSymbolCnt == 3 && computerSymbolCnt == 0) {
      return openEnds >= 2 ? -50000 : -5000;
    }
    if (computerSymbolCnt == 3 && playerSymbolCnt == 0) {
      return openEnds >= 2 ? 25000 : 2500;
    }
  }

  if (computerSymbolCnt == 2 && playerSymbolCnt == 0) {
    return openEnds == 2 ? 1000 : 100;
  }
  if (playerSymbolCnt == 2 && computerSymbolCnt == 0) {
    return openEnds == 2 ? -800 : -80;
  }

  return 0;
}

int heuristicScore(GameSettings * gameSettings, int startRow, int startCol, StreakType streakType, bool computerTurn) {
  int computerSymbolCnt = 0;
  int playerSymbolCnt = 0;

  // Count symbols in the current streak based on streak type
  switch (streakType) {
  case STREAK_ROW:
    for (int i = startCol; i < startCol + 5; i++) {
      if (gameSettings -> gameMap[startRow][i] == SYMBOL_X) {
        playerSymbolCnt++;
      }
      if (gameSettings -> gameMap[startRow][i] == SYMBOL_CIRCLE) {
        computerSymbolCnt++;
      }

    }
    break;

  case STREAK_COLUMN:
    for (int i = startRow; i < startRow + 5; i++) {
      if (gameSettings -> gameMap[i][startCol] == SYMBOL_X) playerSymbolCnt++;
      if (gameSettings -> gameMap[i][startCol] == SYMBOL_CIRCLE) computerSymbolCnt++;
    }
    break;

  case STREAK_RLD:
    for (int i = 0; i < 5; i++) {
      if (gameSettings -> gameMap[startRow + i][startCol - i] == SYMBOL_X) playerSymbolCnt++;
      if (gameSettings -> gameMap[startRow + i][startCol - i] == SYMBOL_CIRCLE) computerSymbolCnt++;
    }
    break;

  case STREAK_LRD:
    for (int i = 0; i < 5; i++) {
      if (gameSettings -> gameMap[startRow + i][startCol + i] == SYMBOL_X) playerSymbolCnt++;
      if (gameSettings -> gameMap[startRow + i][startCol + i] == SYMBOL_CIRCLE) computerSymbolCnt++;
    }
    break;
  }

  // If both player and computer are in the streak -> ignorew
  if (playerSymbolCnt > 0 && computerSymbolCnt > 0) {
    return 0;
  }

  // Calculate open ends
  int openEnds = 0;

  if (streakType == STREAK_ROW) {
    if (startCol > 0 && gameSettings -> gameMap[startRow][startCol - 1] == SYMBOL_BLANK) openEnds++;
    if (startCol + 5 < gameSettings -> mapWidth && gameSettings -> gameMap[startRow][startCol + 5] == SYMBOL_BLANK) openEnds++;
  } else if (streakType == STREAK_COLUMN) {
    if (startRow > 0 && gameSettings -> gameMap[startRow - 1][startCol] == SYMBOL_BLANK) openEnds++;
    if (startRow + 5 < gameSettings -> mapHeight && gameSettings -> gameMap[startRow + 5][startCol] == SYMBOL_BLANK) openEnds++;
  } else if (streakType == STREAK_RLD) {
    if (startRow > 0 && startCol < gameSettings -> mapWidth - 1 && gameSettings -> gameMap[startRow - 1][startCol + 1] == SYMBOL_BLANK) openEnds++;
    if (startRow + 5 < gameSettings -> mapHeight && startCol >= 5 && gameSettings -> gameMap[startRow + 5][startCol - 5] == SYMBOL_BLANK) openEnds++;
  } else if (streakType == STREAK_LRD) {
    if (startRow > 0 && startCol > 0 && gameSettings -> gameMap[startRow - 1][startCol - 1] == SYMBOL_BLANK) openEnds++;

    if (startRow + 5 < gameSettings -> mapHeight && startCol + 5 < gameSettings -> mapWidth && gameSettings -> gameMap[startRow + 5][startCol + 5] == SYMBOL_BLANK) openEnds++;
  }

  return calculateScore(playerSymbolCnt, computerSymbolCnt, openEnds, computerTurn);

}

int heuristicEvaluation(GameSettings * gameSettings, bool computerTurn) {
  int totalScore = 0;

  // Check horizontal
  for (int i = 0; i < gameSettings -> mapHeight; i++) {
    for (int j = 0; j < gameSettings -> mapWidth - 4; j++) {
      int score = heuristicScore(gameSettings, i, j, STREAK_ROW, computerTurn);
      if (score == INT_MAX || score == -INT_MAX) return score;
      totalScore += score;

    }
  }

  // Check vertical
  for (int i = 0; i < gameSettings -> mapHeight - 4; i++) {
    for (int j = 0; j < gameSettings -> mapWidth; j++) {

      int score = heuristicScore(gameSettings, i, j, STREAK_COLUMN, computerTurn);
      if (score == INT_MAX || score == -INT_MAX) return score;
      totalScore += score;

    }
  }

  // Check  RLD
  for (int i = 0; i < gameSettings -> mapHeight - 4; i++) {
    for (int j = 0; j < gameSettings -> mapWidth - 4; j++) {

      int score = heuristicScore(gameSettings, i, j, STREAK_RLD, computerTurn);
      if (score == INT_MAX || score == -INT_MAX) return score;
      totalScore += score;

    }
  }

  // Check  LRD
  for (int i = 0; i < gameSettings -> mapHeight - 4; i++) {
    for (int j = 4; j < gameSettings -> mapWidth; j++) {

      int score = heuristicScore(gameSettings, i, j, STREAK_LRD, computerTurn);
      if (score == INT_MAX || score == -INT_MAX) return score;
      totalScore += score;

    }
  }
  return totalScore;
}

int minimax(GameSettings * gameSettings, int depth, bool computerTurn, int alpha, int beta, int maxDepth) {

  if (depth >= maxDepth) {
    return heuristicEvaluation(gameSettings, computerTurn);
  }

  if (checkWin(gameSettings, SYMBOL_X)) return -INT_MAX;
  if (checkWin(gameSettings, SYMBOL_CIRCLE)) return INT_MAX;
  if (isBoardFull(gameSettings)) return 0;

  if (computerTurn) {
    int bestScore = INT_MIN;
    bool shouldBreak = false;

    for (int i = 0; i < gameSettings -> mapHeight && !shouldBreak; i++) {
      for (int j = 0; j < gameSettings -> mapWidth; j++) {
        if (isWorthTrying(gameSettings, i, j)) {
          makeMove(i, j, gameSettings, SYMBOL_CIRCLE);
          int score = minimax(gameSettings, depth + 1, false, alpha, beta, maxDepth);
          undoMove(i, j, gameSettings);

          bestScore = max(bestScore, score);
          alpha = max(alpha, bestScore);

          if (beta <= alpha) {
            shouldBreak = true;
            break;
          }
        }
      }
    }
    return bestScore;
  } else {
    int bestScore = INT_MAX;
    bool shouldBreak = false;

    for (int i = 0; i < gameSettings -> mapHeight && !shouldBreak; i++) {
      for (int j = 0; j < gameSettings -> mapWidth; j++) {
        if (isWorthTrying(gameSettings, i, j)) {
          makeMove(i, j, gameSettings, SYMBOL_X);
          int score = minimax(gameSettings, depth + 1, true, alpha, beta, maxDepth);
          undoMove(i, j, gameSettings);

          bestScore = min(bestScore, score);
          beta = min(beta, bestScore);

          if (beta <= alpha) {
            shouldBreak = true;
            break;
          }
        }
      }
    }
    return bestScore;
  }
}

Position findBestMove(GameSettings * gameSettings, int maxDepth) {
  Position bestMove = {
    gameSettings -> mapHeight / 2,
    gameSettings -> mapWidth / 2
  };
  int bestScore = INT_MIN;
  int alpha = INT_MIN;
  int beta = INT_MAX;

  for (int i = 0; i < gameSettings -> mapHeight; i++) {
    for (int j = 0; j < gameSettings -> mapWidth; j++) {
      if (isWorthTrying(gameSettings, i, j)) {
        makeMove(i, j, gameSettings, SYMBOL_CIRCLE);
        int score = minimax(gameSettings, 0, false, alpha, beta, maxDepth);

        undoMove(i, j, gameSettings);
        if (score == INT_MAX) {
          bestMove.x = i;
          bestMove.y = j;
          return bestMove;
        }
        if (score > bestScore) {
          bestScore = score;
          bestMove.x = i;
          bestMove.y = j;
        }
      }
    }
  }

  return bestMove;
}
