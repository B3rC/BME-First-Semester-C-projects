#include "setupmenu.h"

#include "creategraphic.h"

#include "check.h"

#include "main.h"

#include "menu.h"

#include <stdio.h>

#include "structures.h"

#include "game.h"

#include "debugmalloc.h"

void setupmenu() {

  GameSettings settings;

  settings.mapWidth = 6;
  settings.mapHeight = 6;
  settings.difficulty = DIFFICULTY_NORMAL;
  settings.difficulty = NEXT_PLAYER;

  char width_to_str[12];
  char height_to_str[12];

  createSetupMenu(renderer);

  sprintf(width_to_str, "%d", settings.mapWidth);
  sprintf(height_to_str, "%d", settings.mapHeight);

  SDL_RenderPresent(renderer);

  SDL_Event ev;

  while (SDL_WaitEvent( & ev) && ev.type != SDL_QUIT) {
    if (ev.type != SDL_MOUSEBUTTONDOWN) continue;
    SDL_Point mousePos;

    mousePos.x = ev.motion.x;
    mousePos.y = ev.motion.y;

    //Map width increment
    if (isInRectangle(mousePos, 1110, 380, 75, 75)) {
      if (settings.mapWidth < 10)
        settings.mapWidth++;

      sprintf(width_to_str, "%d", settings.mapWidth);
      dynamicText(width_to_str, renderer, 960, 380, 100, 100, 80, beige, black);

    }
    //Map width decrement
    else if (isInRectangle(mousePos, 810, 380, 75, 75)) {

      if (settings.mapWidth > 6)
        settings.mapWidth--;

      sprintf(width_to_str, "%d", settings.mapWidth);
      dynamicText(width_to_str, renderer, 960, 380, 100, 100, 80, beige, black);
    }

    //Map height increment
    else if (isInRectangle(mousePos, 1110, 580, 75, 75)) {

      if (settings.mapHeight < 10)
        settings.mapHeight++;

      sprintf(height_to_str, "%d", settings.mapHeight);
      dynamicText(height_to_str, renderer, 960, 580, 100, 100, 80, beige, black);
    }
    //Map height decrement
    else if (isInRectangle(mousePos, 810, 580, 75, 75)) {

      if (settings.mapHeight > 6)
        settings.mapHeight--;

      sprintf(height_to_str, "%d", settings.mapHeight);
      dynamicText(height_to_str, renderer, 960, 580, 100, 100, 80, beige, black);

    }

    //Normal difficulty
    else if (isInRectangle(mousePos, 635, 805, 175, 75)) {
      dynamicText("Normal", renderer, 635, 805, 175, 75, 72, green, black);
      dynamicText("Hard", renderer, 835, 805, 175, 75, 72, red, black);

      settings.difficulty = DIFFICULTY_NORMAL;
    }

    //Hard difficulty
    else if (isInRectangle(mousePos, 835, 805, 175, 75)) {
      dynamicText("Hard", renderer, 835, 805, 175, 75, 72, green, black);
      dynamicText("Normal", renderer, 635, 805, 175, 75, 72, red, black);

      settings.difficulty = DIFFICULTY_HARD;
    }

    //Computer starts
    else if (isInRectangle(mousePos, 1085, 805, 175, 75)) {
      dynamicText("Player", renderer, 1085, 805, 175, 75, 72, green, black);
      dynamicText("Computer", renderer, 1285, 805, 175, 75, 72, red, black);

      settings.nextToMove = NEXT_PLAYER;
    }

    //Player starts
    else if (isInRectangle(mousePos, 1285, 805, 175, 75)) {
      dynamicText("Player", renderer, 1085, 805, 175, 75, 72, red, black);
      dynamicText("Computer", renderer, 1285, 805, 175, 75, 72, green, black);

      settings.nextToMove = NEXT_COMPUTER;
    }

    //Start game
    else if (isInRectangle(mousePos, 960, 950, 200, 100)) {
      Game(settings, false);
      settings.mapWidth = 6;
      settings.mapHeight = 6;
      settings.difficulty = DIFFICULTY_NORMAL;
      settings.nextToMove = NEXT_PLAYER;

      createSetupMenu(renderer);

    } else if (isInRectangle(mousePos, 1650, 940, 300, 100)) {
      return;
    }

  }

}
