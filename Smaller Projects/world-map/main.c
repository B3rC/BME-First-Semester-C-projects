#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "external.h"


typedef struct CoordinatesArray{
    int16_t *vx, *vy;
    int size;
}CoordinatesArray;

void handle_coordinates(CoordinatesArray* coords, const float* data, SDL_Renderer *renderer, Uint16 r, Uint16 g, Uint16 b, Uint16 a);

void transform_coordinates(CoordinatesArray* coords, const float* coordinates);

void draw_coordinates(CoordinatesArray* from, SDL_Renderer *renderer, Uint16 r, Uint16 g, Uint16 b, Uint16 a);


/* create window */
void sdl_init(char const *title, int width, int height, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("SDL could not be initialized: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == NULL) {
        SDL_Log("Window could not be created: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Renderer could not be created: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}



int main(int argc, char *argv[]) {

    CoordinatesArray lakes_coords, land_coords;


    /* create window */
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("World Map", 1080, 540, &window, &renderer);


    // Color oceans (background)
    SDL_SetRenderDrawColor(renderer, 36, 36, 221, 255);
    SDL_RenderClear(renderer);


    // Handle land and lakes coordinates
    handle_coordinates(&land_coords, land, renderer, 126,245,126,255);
    handle_coordinates(&lakes_coords, lakes, renderer, 36,36,221,255);

    // BME initialization
    float const bme[2] = {19.040236, 47.497913};
    int bme_coords[2] = {540 + ((bme[0]/180)*540), 270 -((bme[1]/90)*270)};

    // Mark BME
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    circleRGBA(renderer, bme_coords[0], bme_coords[1], 3, 255,0,0,255);

    // Draw lines faintly
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50);
    for(int i = 0; i < 24; i++){
        // Longitude lines
        SDL_RenderDrawLine(renderer, 0 + i * (1080 / 24), 0, 0 + i * (1080 / 24), 540);

        // Latitude lines
        if(i < 12){
            SDL_RenderDrawLine(renderer, 0, 0 + i * (540 / 12), 1080, 0 + i * (540 / 12));
        }
    }


    /* update screen with drawn content */
    SDL_RenderPresent(renderer);

    /* exit */
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        if (ev.type == SDL_MOUSEBUTTONDOWN) {
            if (ev.button.windowID == SDL_GetWindowID(window)) {
                break;
            }
        }
    }


    /* close window */
    SDL_Quit();

    return 0;
}

void handle_coordinates(CoordinatesArray* coords, const float* data, SDL_Renderer *renderer, Uint16 r, Uint16 g, Uint16 b, Uint16 a) {
    int size = 0;
    int n = 0;
    int previous = 0;

    while (data[n] != -1 || data[n+1] != -1) {

        if (data[n] == 0 && data[n+1] == 0 ) {
            coords->size = size / 2;
            coords->vx = (int16_t*) malloc(coords->size * sizeof(int16_t));
            coords->vy = (int16_t*) malloc(coords->size * sizeof(int16_t));
            if (coords->vx == NULL || coords->vy == NULL) {
                exit(1);
            }

            transform_coordinates(coords, data + previous + 1);
            draw_coordinates(coords, renderer, r, g, b, a);

            // Free memory
            free(coords->vx);
            free(coords->vy);

            size = 0;
            previous = n + 1;
        }
        n++;
        size++;
    }
}

void transform_coordinates(CoordinatesArray* coords, const float* coordinates) {
    int n = 0;

    for(int i = 0; i < coords->size; i++){
        coords->vx[i] = 540 + ((coordinates[n] / 180) * 540);
        coords->vy[i] = 270 - ((coordinates[++n] / 90) * 270);
        n++;
    }
}

void draw_coordinates(CoordinatesArray* from, SDL_Renderer *renderer, Uint16 r, Uint16 g, Uint16 b, Uint16 a) {
    filledPolygonRGBA(renderer, from->vx, from->vy, from->size - 1, r, g, b, a);
    aapolygonRGBA(renderer, from->vx, from->vy, from->size - 1, 0, 0, 0, 255);
}
