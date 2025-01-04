#include "game.h"

#include "main.h"

#include "creategraphic.h"

#include <stdlib.h>

#include <stdio.h>

#include "debugmalloc.h"

#include "check.h"

#include "computer.h"

#include "init.h"

#include "filehandling.h"

void Game(GameSettings gameSettings, bool loadFromFile) {
  GameSettings settings;

  if (loadFromFile) {
    if (!initSettingsFromFile( & settings)) {
      printf("Error occured");
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Load Error", "An error has occurred. Are you sure you have a saved game?", NULL);

      return;
    }
  } else {
    settings = gameSettings;
    if (!GameMap_Init( & settings)) {
      printf("Error occured");
      return;
    }

  }

  double cellSize;
  cellSize = (settings.mapHeight > settings.mapWidth) ? 900 / (double) settings.mapHeight : 900 / (double) settings.mapWidth;
  createGameGraphics(renderer, & settings);

  if (checkWin( & settings, SYMBOL_CIRCLE)) {
    dynamicText("Computer won", renderer, 1440, 500, 400, 200, 100, red, black);
    settings.nextToMove = NEXT_NONE;
  } else if (checkWin( & settings, SYMBOL_X)) {
    dynamicText("Player won", renderer, 1440, 500, 400, 200, 100, blue, white);
    settings.nextToMove = NEXT_NONE;

  } else if (isBoardFull( & settings)) {
    dynamicText("Draw", renderer, 1440, 500, 400, 200, 100, grey, black);
    settings.nextToMove = NEXT_NONE;

  }

  //Who moves next when game is loaded
  if(settings.nextToMove == NEXT_PLAYER){
    dynamicText("Player", renderer, 1600, 140, 300, 100, 100, beige, blue);

  }
  else if(settings.nextToMove == NEXT_COMPUTER){
    dynamicText("Computer", renderer, 1600, 140, 300, 100, 100, beige, red);

  }
  else dynamicText("None", renderer, 1600, 140, 300, 100, 100, beige, black);


  SDL_Event ev;

  while (SDL_WaitEvent( & ev) && ev.type != SDL_QUIT) {

    SDL_Point mousePos;

    if (settings.nextToMove == NEXT_COMPUTER) {
      makeComputerMove( & settings);
      createGameGraphics(renderer, & settings);
      if (checkWin( & settings, SYMBOL_CIRCLE)) {
        dynamicText("Computer won", renderer, 1440, 500, 400, 200, 100, red, black);
        settings.nextToMove = NEXT_NONE;
      } else if (isBoardFull( & settings)) {
        dynamicText("Draw", renderer, 1440, 500, 400, 200, 100, grey, black);
        settings.nextToMove = NEXT_NONE;

      } else {
        dynamicText("Player", renderer, 1600, 140, 300, 100, 100, beige, blue);

        settings.nextToMove = NEXT_PLAYER;

      }
    }

    if (ev.type != SDL_MOUSEBUTTONDOWN) continue;

    mousePos.x = ev.motion.x;
    mousePos.y = ev.motion.y;
    if (isInGameArea(mousePos, 90, 90, 90 + settings.mapWidth * cellSize, 90 + settings.mapHeight * cellSize)) {
      int row = ((mousePos.y - 90) / (cellSize));
      int column = ((mousePos.x - 90) / (cellSize));

      if (settings.nextToMove == NEXT_PLAYER && isLegitMove(row, column, & settings)) {

        makePlayerMove( & settings, mousePos, cellSize);
        createGameGraphics(renderer, & settings);
        if (checkWin( & settings, SYMBOL_X)) {
          dynamicText("Player won", renderer, 1440, 500, 400, 200, 100, blue, white);
          settings.nextToMove = NEXT_NONE;
        } else if (isBoardFull( & settings)) {
          dynamicText("Draw", renderer, 1440, 500, 400, 200, 100, grey, white);

        } else {
          dynamicText("Computer", renderer, 1600, 140, 300, 100, 100, beige, red);

          settings.nextToMove = NEXT_COMPUTER;

        }
      }

    } else if (isInRectangle(mousePos, 1300, 940, 300, 100)) {

      if (saveGame( & settings)) {
        dynamicText("SAVED", renderer, 1300, 940, 300, 100, 100, green, black);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Saved", "The current state of the game has been saved.", NULL);

      } else {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save Error", "An error has occurred! You can try again. Click OK to continue.", NULL);

      }

    } else if (isInRectangle(mousePos, 1650, 940, 300, 100)) {
      GameMap_Memory_Free( & settings);
      return;
    }

  }

  GameMap_Memory_Free( & settings);
}

bool GameMap_Init(GameSettings * gameSettings) {
  gameSettings -> gameMap = (GameMap ** ) malloc(gameSettings -> mapHeight * sizeof(GameMap * ));
  if (gameSettings -> gameMap == NULL) {
    return false;
  }

  for (int i = 0; i < gameSettings -> mapHeight; i++) {
    gameSettings -> gameMap[i] = (GameMap * ) malloc(gameSettings -> mapWidth * sizeof(GameMap));
    if (gameSettings -> gameMap[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(gameSettings -> gameMap[j]);
      }
      free(gameSettings -> gameMap);
      return false;
    }
  }

  for (int i = 0; i < gameSettings -> mapHeight; i++) {
    for (int j = 0; j < gameSettings -> mapWidth; j++) {
      gameSettings -> gameMap[i][j] = SYMBOL_BLANK;
    }
  }

  return true;
}


void GameMap_Memory_Free(GameSettings * gameSettings) {
  for (int i = 0; i < gameSettings -> mapHeight; ++i) {
    free(gameSettings -> gameMap[i]);
  }
  free(gameSettings -> gameMap);
}

void makePlayerMove(GameSettings * gameSettings, SDL_Point mousePos, int cellSize) {
  int i = ((mousePos.y - 90) / cellSize);
  int j = ((mousePos.x - 90) / cellSize);

  gameSettings -> gameMap[i][j] = SYMBOL_X;
}

void makeComputerMove(GameSettings * gameSettings) {
  if (gameSettings -> difficulty == DIFFICULTY_NORMAL) {
    makeNormalModeMove(gameSettings);
  }
  if (gameSettings -> difficulty == DIFFICULTY_HARD) {
    makeHardModeMove(gameSettings);
  }
}
