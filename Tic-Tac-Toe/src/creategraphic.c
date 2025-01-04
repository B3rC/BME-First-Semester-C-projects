#include "creategraphic.h"

#include <SDL2/SDL.h>

#include <SDL2/SDL2_gfxPrimitives.h>

#include <SDL2/SDL_ttf.h>

#include "structures.h"

#include <stdio.h>

void createBtn(char * text, SDL_Renderer * renderer, int x, int y, int w, int h, int fontSize, SDL_Color backgroundColor, SDL_Color fontColor, SDL_Color borderColor) {
  boxRGBA(renderer, (x - (w + 5) / 2), (y - (h + 5) / 2), (x + (w + 5) / 2), (y + (h + 5) / 2), borderColor.r, borderColor.g, borderColor.b, borderColor.a);

  boxRGBA(renderer, (x - w / 2), (y - h / 2), (x + w / 2), (y + h / 2), backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

  createText(text, renderer, x, y, 0.75 * w, 0.75 * h, fontSize, fontColor);

}

/*based on infoc SDL articles*/
void createText(char * text, SDL_Renderer * renderer, int x, int y, int w, int h, int fontSize, SDL_Color color) {
  TTF_Init();
  TTF_Font * font = TTF_OpenFont("assets/font.ttf", fontSize);

  SDL_Surface * felirat;
  SDL_Texture * felirat_t;
  SDL_Rect hova = {
    0,
    0,
    0,
    0
  };

  felirat = TTF_RenderUTF8_Blended(font, text, color);
  felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
  hova.x = (x - w / 2);
  hova.y = (y - h / 2);
  hova.w = w;
  hova.h = h;
  SDL_RenderCopy(renderer, felirat_t, NULL, & hova);
  SDL_FreeSurface(felirat);
  SDL_DestroyTexture(felirat_t);

}

void createMenu(SDL_Renderer * renderer) {

  SDL_SetRenderDrawColor(renderer, beige.r, beige.g, beige.b, beige.a);
  SDL_RenderClear(renderer);
  createText("Tic", renderer, 790, 150, 150, 150, 140, blue);
  createText("Tac", renderer, 960, 150, 150, 150, 140, red);
  createText("Toe", renderer, 1130, 150, 150, 150, 140, black);

  //New game button
  createBtn("New Game", renderer, 960, 375, 500, 150, 100, white, black, black);

  //Load game btn
  createBtn("Load Game", renderer, 960, 575, 500, 150, 100, white, black, black);

  //Quit
  createBtn("Quit Game", renderer, 960, 775, 500, 150, 100, white, black, black);

  SDL_RenderPresent(renderer);
  SDL_RenderPresent(renderer);

}

void createSetupMenu(SDL_Renderer * renderer) {

  SDL_SetRenderDrawColor(renderer, 245, 245, 210, 255);
  SDL_RenderClear(renderer);

  createText("Create new game", renderer, 960, 130, 550, 150, 140, black);
  thickLineRGBA(renderer, 735, 200, 1185, 200, 5, 0, 0, 0, 255);

  //Map width setting elements
  createText("Map width", renderer, 960, 275, 300, 100, 72, black);
  createBtn("+", renderer, 1110, 380, 75, 75, 175, red, black, black);
  createBtn("-", renderer, 810, 380, 75, 75, 175, red, black, black);
  createText("6", renderer, 960, 380, 100, 100, 80, black);

  //Map height setting elements
  createText("Map height", renderer, 960, 475, 300, 100, 72, black);
  createBtn("+", renderer, 1110, 580, 75, 75, 175, red, black, black);
  createBtn("-", renderer, 810, 580, 75, 75, 175, red, black, black);
  createText("6", renderer, 960, 580, 100, 100, 80, black);

  //Difficulty elements
  createText("Difficulty", renderer, 735, 700, 300, 100, 72, black);
  createBtn("Hard", renderer, 835, 805, 175, 75, 72, red, black, black);
  createBtn("Normal", renderer, 635, 805, 175, 75, 72, red, black, black);
  dynamicText("Normal", renderer, 635, 805, 175, 75, 72, green, black);

  //Who starts
  createText("Who starts", renderer, 1185, 700, 300, 100, 72, black);
  createBtn("Computer", renderer, 1285, 805, 175, 75, 72, red, black, black);
  createBtn("Player", renderer, 1085, 805, 175, 75, 72, red, black, black);

  dynamicText("Player", renderer, 1085, 805, 175, 75, 72, green, black);
  dynamicText("Computer", renderer, 1285, 805, 175, 75, 72, red, black);

  createBtn("GO!", renderer, 960, 950, 200, 100, 75, red, black, black);
  createBtn("QUIT", renderer, 1650, 940, 300, 100, 100, light_red, black, black);

  SDL_RenderPresent(renderer);
}

void createGameGraphics(SDL_Renderer * renderer, GameSettings * settings) {

  SDL_SetRenderDrawColor(renderer, 245, 245, 210, 255);
  SDL_RenderClear(renderer);

  double cellSize;
  cellSize = (settings -> mapHeight > settings -> mapWidth) ? 900 / (double) settings -> mapHeight : 900 / (double) settings -> mapWidth;
  boxRGBA(renderer, 90, 90, 90 + settings -> mapWidth * cellSize, 90 + settings -> mapHeight * cellSize, white.r, white.g, white.b, white.a);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  createText("Next: ", renderer, 1300, 140, 300, 100, 100, black);

  createBtn("SAVE GAME", renderer, 1300, 940, 300, 100, 100, light_green, black, black);
  createBtn("QUIT", renderer, 1650, 940, 300, 100, 100, light_red, black, black);

  //Draw map state
  for (int i = 0; i < settings -> mapHeight; i++) {
    for (int j = 0; j < settings -> mapWidth; j++) {

      //Drawing circle (computer)
      if (settings -> gameMap[i][j] == SYMBOL_CIRCLE) {
        filledCircleRGBA(renderer, (90 + j * cellSize) + cellSize / 2, (90 + i * cellSize) + cellSize / 2, cellSize / 2.10, red.r, red.g, red.b, red.a);

        filledCircleRGBA(renderer, (90 + j * cellSize) + cellSize / 2, (90 + i * cellSize) + cellSize / 2, cellSize / 2.35, white.r, white.g, white.b, white.a);
      }

      //Drawing X (player)
      if (settings -> gameMap[i][j] == SYMBOL_X) {
        thickLineRGBA(renderer, (90 + j * cellSize), (90 + i * cellSize), (90 + j * cellSize) + cellSize, (90 + i * cellSize) + cellSize, 3, 0, 0, 255, 255);
        thickLineRGBA(renderer, (90 + (j * cellSize)), (90 + i * cellSize) + cellSize, (90 + j * cellSize) + cellSize, (90 + i * cellSize), 3, 0, 0, 255, 255);
      }
    }
  }

  //Draw GRID Vertical lines
  for (int i = 0; i <= settings -> mapWidth; i++) {
    thickLineRGBA(renderer, 90 + i * cellSize, 90, 90 + i * cellSize, 90 + settings -> mapHeight * cellSize, 3, 0, 0, 0, 255);
  }
  //Draw GRID Horizonzal lines
  for (int i = 0; i <= settings -> mapHeight; i++) {
    thickLineRGBA(renderer, 90, 90 + i * cellSize, 90 + settings -> mapWidth * cellSize, 90 + i * cellSize, 3, 0, 0, 0, 255);

  }

  SDL_RenderPresent(renderer);

}

void dynamicText(char * text, SDL_Renderer * renderer, int x, int y, int w, int h, int fontSize, SDL_Color bg_color, SDL_Color txt_color) {
  SDL_Rect dynamicArea = {
    x - w / 2,
    y - h / 2,
    w,
    h
  };
  SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
  SDL_RenderFillRect(renderer, & dynamicArea);
  createText(text, renderer, x, y, 0.9 * w, h, fontSize, txt_color);
  SDL_RenderPresent(renderer);
}
