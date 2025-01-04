#include "structures.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#ifndef CREATEGRAPHIC_H_INCLUDED
#define CREATEGRAPHIC_H_INCLUDED

/**
 * @brief Creates the main menu screen.
 *
 * This function creates the main menu with options for starting a new game, loading a saved game,
 * and quitting the application.
 *
 * @param renderer The SDL_Renderer used to render the menu elements.
 */
void createMenu(SDL_Renderer* renderer);

/**
 * @brief Creates the game graphics and screen.
 *
 * This function creates and renders the game with the given values.
 *
 * @param renderer The SDL_Renderer used to render the menu elements.
 * @param game A pointer to the game settings containing the current game settings.
 *
 */
void createGameGraphics(SDL_Renderer* renderer, GameSettings* settings);

/**
 * @brief Creates a text with given string.
 *
 * This function creates a given text string with the specified position, width, height, font size, and color.
 *
 * @param text The text to render.
 * @param renderer The SDL_Renderer used to render the text.
 * @param x The x coordinate of the text center.
 * @param y The y coordinate of the text center.
 * @param w The width of the text box.
 * @param h The height of the text box.
 * @param fontSize The font size of the text.
 * @param color The color of the text.
 */
void createText(char* text, SDL_Renderer* renderer, int x,int y,int w,int h,int fontSize, SDL_Color color);

/**
 * @brief Creates the setup menu screen.
 *
 * This function creates the setup menu with options for configuring the game map width, height, difficulty, first to move.
 *
 * @param renderer The SDL_Renderer used to render the setup menu elements.
 */
void createSetupMenu(SDL_Renderer* renderer);

/**
 * @brief Creates a button with text.
 *
 * This function creates a button with specified text, background color, font color, and border color.
 *
 * @param text The text to on the button.
 * @param renderer The SDL_Renderer used to render the button.
 * @param x The x coordinate of the button center.
 * @param y The y coordinate of the button center.
 * @param w The width of the button.
 * @param h The height of the button.
 * @param fontSize The font size of the button text.
 * @param backgroundColor The background color of the button.
 * @param fontColor The font color of the button text.
 * @param borderColor The border color of the button.
 */
void createBtn(char* text, SDL_Renderer* renderer, int x,int y,int w,int h,int fontSize, SDL_Color backgroundColor, SDL_Color fontColor, SDL_Color borderColor);

void dynamicText(char* text, SDL_Renderer* renderer, int x,int y,int w,int h,int fontSize, SDL_Color bg_color, SDL_Color txt_color);

#endif // CREATEGRAPHIC_H_INCLUDED
