#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdbool.h>

#include "game.h"

/* **************************************************************** */
     
#ifdef __ANDROID__ 
#define PRINT(STR, ...) do { SDL_Log(STR, ##__VA_ARGS__);  } while(0)
#define ERROR(STR, ...) do { SDL_Log(STR, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)
#else
#define PRINT(STR, ...) do { printf(STR, ##__VA_ARGS__); } while(0)
#define ERROR(STR, ...) do { fprintf(stderr, STR, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)
#endif

/* **************************************************************** */
     
#define APP_NAME "Gyges"
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define DELAY 20
#define OFFSET 95
#define CELL_SIZE 70
#define TEXT_COLOR 250, 165, 62
#define RED_COLOR 255, 15, 3
#define GREEN_COLOR 71, 169, 71
#define GRAY_COLOR 150, 150, 150
#define BLUE_COLOR 0, 198, 255
#define FONT_SIZE 80

#define GYGES_BOARD "assets/gyges-board.png"
#define TILEMAP "assets/tilemap.png"
#define SWAP_ICON "assets/swap-icon.png"
#define CONTINUE_ICON "assets/continue-icon.png"

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]);
void render(SDL_Window* win, SDL_Renderer* ren, Env * env);
void clean(SDL_Window* win, SDL_Renderer* ren, Env * env);
bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);

/* **************************************************************** */

#endif
