// SDL2 Model by aurelien.esnard@u-bordeaux.fr

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
#define GREEN_COLOR 169, 71, 71
#define FONT_SIZE 80

#define GYGES_BOARD "assets/gyges-board.png"
#define GYGES_P1 "assets/gyges-p1.png"
#define GYGES_P2 "assets/gyges-p2.png"
#define GYGES_P3 "assets/gyges-p3.png"
#define GYGES_P1_SELECTED "assets/gyges-p1-selected.png"
#define GYGES_P2_SELECTED "assets/gyges-p2-selected.png"
#define GYGES_P3_SELECTED "assets/gyges-p3-selected.png"
#define GYGES_P1_HOVERED "assets/gyges-p1-hovered.png"
#define GYGES_P2_HOVERED "assets/gyges-p2-hovered.png"
#define GYGES_P3_HOVERED "assets/gyges-p3-hovered.png"
#define TILEMAP "assets/tilemap.png"

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]);
void render(SDL_Window* win, SDL_Renderer* ren, Env * env);
void clean(SDL_Window* win, SDL_Renderer* ren, Env * env);
bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);

/* **************************************************************** */

#endif
