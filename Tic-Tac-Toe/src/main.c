#include <SDL2/SDL.h>

#include <SDL2/SDL2_gfxPrimitives.h>

#include <math.h>

#include <stdlib.h>

#include "init.h"

#include "menu.h"

#include "debugmalloc.h"

SDL_Window * window;
SDL_Renderer * renderer;

int main(int argc, char * argv[]) {

  sdl_initialize();

  menu();

  SDL_Quit();

  return 0;
}
