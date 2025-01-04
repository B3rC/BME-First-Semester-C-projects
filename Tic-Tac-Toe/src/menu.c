#include "creategraphic.h"

#include "check.h"

#include "main.h"

#include <stdio.h>

#include "setupmenu.h"

#include "game.h"

#include "debugmalloc.h"

void menu() {
  createMenu(renderer);

  SDL_Event ev;
  while (SDL_WaitEvent( & ev) && ev.type != SDL_QUIT) {
    SDL_Point mousePos;
    if (ev.type != SDL_MOUSEBUTTONDOWN) continue;

    mousePos.x = ev.motion.x;
    mousePos.y = ev.motion.y;

    //Load setupmenu
    if (isInRectangle(mousePos, 960, 375, 500, 150)) {

      setupmenu();
      createMenu(renderer);
    }
    //Load saved game
    else if (isInRectangle(mousePos, 960, 575, 500, 150)) {
      GameSettings settings;

      Game(settings, true);
      createMenu(renderer);

    }
    //QUIT :(
    else if (isInRectangle(mousePos, 960, 775, 500, 150)) {
      return;
    }

  }
}
