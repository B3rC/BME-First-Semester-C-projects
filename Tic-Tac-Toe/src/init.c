#include <SDL2/SDL.h>

#include <SDL2/SDL2_gfxPrimitives.h>

#include "main.h"

#include "init.h"

#include <stdio.h>

#include "debugmalloc.h"

void sdl_initialize() {

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
    exit(1);
  }
  window = SDL_CreateWindow("Kozmamoba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
  if (window == NULL) {
    SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
    exit(1);
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == NULL) {
    SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
    exit(1);
  }
  SDL_RenderClear(renderer);

}
