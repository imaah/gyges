// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // required to load transparent texture from PNG

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "window.h"
#include "board.h"
#include "game.h"

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[])
{
    Env *env = malloc(sizeof(struct Env_t));

    int w, h;
    SDL_GetWindowSize(win, &w, &h);

    env->gray_piece = 0;
    env->selected_piece = 245;
    env->normal_piece = 490;
    env->hovered_piece = 735;

    SDL_Rect sr = {0, 735, 245, 245};

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    env->shadow_rect = sr;
    TTF_Font *sans = TTF_OpenFont("assets/fonts/Font.ttf", FONT_SIZE);
    env->font = sans;

    // loading textures
    env->background = IMG_LoadTexture(ren, GYGES_BOARD);
    if (!env->background)
        ERROR("IMG_LoadTexture: %s\n", GYGES_BOARD);

    env->tilemap = IMG_LoadTexture(ren, TILEMAP);
    if (!env->tilemap)
        ERROR("IMG_LoadTexture: %s\n", TILEMAP);

    // env->piece_1 = IMG_LoadTexture(ren, GYGES_P1);
    // if (!env->background)
    //     ERROR("IMG_LoadTexture: %s\n", GYGES_P1);

    // env->piece_1_selected = IMG_LoadTexture(ren, GYGES_P1_SELECTED);
    // if (!env->background)
    //     ERROR("IMG_LoadTexture: %s\n", GYGES_P1_SELECTED);

    // env->piece_2 = IMG_LoadTexture(ren, GYGES_P2);
    // if (!env->background)
    //     ERROR("IMG_LoadTexture: %s\n", GYGES_P2);

    // env->piece_2_selected = IMG_LoadTexture(ren, GYGES_P2_SELECTED);
    // if (!env->background)
    //     ERROR("IMG_LoadTexture: %s\n", GYGES_P2_SELECTED);

    // env->piece_3 = IMG_LoadTexture(ren, GYGES_P3);
    // if (!env->background)
    //     ERROR("IMG_LoadTexture: %s\n", GYGES_P3);

    // env->piece_3_selected = IMG_LoadTexture(ren, GYGES_P3_SELECTED);
    // if (!env->background)
    //     ERROR("IMG_LoadTexture: %s\n", GYGES_P3_SELECTED);

    // game variables
    env->game = new_game();
    env->current_player = SOUTH_P;
    env->current_state = INI_SELECT_SPOT;

    env->clicked_line = -1;
    env->clicked_column = -1;

    env->selected_column = -1;

    env->err_msg = malloc(sizeof(char) * 255);
    env->info_msg = malloc(sizeof(char) * 255);

    place_piece(env->game, ONE, env->current_player, 0);
    place_piece(env->game, TWO, env->current_player, 1);
    place_piece(env->game, THREE, env->current_player, 2);

    return env;
}

/* **************************************************************** */

void set_piece_rect(SDL_Rect *rect, float line, float column)
{
    rect->x = OFFSET + column * CELL_SIZE;
    rect->y = OFFSET + line * CELL_SIZE;
    rect->h = CELL_SIZE - 10;
    rect->w = CELL_SIZE - 10;
}

void display_message(Env *env, SDL_Renderer *ren, char *message_content, bool is_error)
{
    SDL_Surface *broadcastMessage;

    if (is_error)
    {
        SDL_Color color = {RED_COLOR};
        broadcastMessage = TTF_RenderUTF8_Blended(env->font, message_content, color);
    }
    else
    {
        SDL_Color color = {RED_COLOR};
        broadcastMessage = TTF_RenderUTF8_Blended(env->font, message_content, color);
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(ren, broadcastMessage);

    SDL_Rect background = {SCREEN_WIDTH / 2 - 5 - strlen(message_content) * (FONT_SIZE / 9.4), SCREEN_HEIGHT / 4 - FONT_SIZE / 6, strlen(message_content) * (FONT_SIZE / 4.7) + 10, FONT_SIZE / 3};

    if (is_error != true)
    {
        background.y = SCREEN_HEIGHT / 4 + FONT_SIZE / 6;
    }

    SDL_SetRenderDrawColor(ren, 255, 167, 60, 128);

    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(ren, &background);
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_INVALID);

    SDL_RenderCopy(ren, message, NULL, &background);
}

void render_piece(SDL_Renderer *ren, Env *env, size piece_size, float line, float column)
{
    SDL_Rect rect;
    set_piece_rect(&rect, line, column);
    if (piece_size != NONE)
    {
        SDL_Rect crop = {env->normal_piece, (piece_size - 1) * 245, 245, 245};

        SDL_RenderCopy(ren, env->tilemap, &crop, &rect);
    }
}

void render_selected_piece(SDL_Renderer *ren, Env *env, size piece_size, float line, float column)
{
    SDL_Rect rect;
    set_piece_rect(&rect, line, column);
    if (piece_size != NONE)
    {
        SDL_Rect crop = {env->selected_piece, (piece_size - 1) * 245, 245, 245};

        SDL_RenderCopy(ren, env->tilemap, &crop, &rect);
    }
}

void render_hovered_piece(SDL_Renderer *ren, Env *env, size piece_size, float line, float column)
{
    SDL_Rect rect;
    set_piece_rect(&rect, line, column);
    if (piece_size != NONE)
    {
        SDL_Rect crop = {env->hovered_piece, (piece_size - 1) * 245, 245, 245};
        SDL_RenderCopy(ren, env->tilemap, &crop, &rect);
    }
}

void render_shadow(Env *env, SDL_Renderer *ren, int line, int column)
{
    SDL_Rect rect;
    set_piece_rect(&rect, line, column);
    SDL_RenderCopy(ren, env->tilemap, &env->shadow_rect, &rect);
}

void render(SDL_Window *win, SDL_Renderer *ren, Env *env)
{
    /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
    SDL_RenderCopy(ren, env->background, NULL, NULL);
    board game = env->game;

    int picked_line = picked_piece_line(game);
    int picked_column = picked_piece_column(game);
    player picked_owner = picked_piece_owner(game);
    size picked_size = picked_piece_size(game);

    size south_goal_size = get_goal_piece(game, SOUTH_P);
    size north_goal_size = get_goal_piece(game, NORTH_P);

    render_piece(ren, env, south_goal_size, -1, 3.5);
    render_piece(ren, env, north_goal_size, 6, 3.5);

    // Getting the mouse position to render a different piece sprite
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    int hovered_line = (mouse_y - OFFSET) / CELL_SIZE;
    int hovered_column = (mouse_x - OFFSET) / CELL_SIZE;

    for (int line = 0; line < DIMENSION; line++)
    {
        // Looping through columns
        for (int column = 0; column < DIMENSION; column++)
        {
            // Getting which piece to place in these coordinates
            size piece = get_piece_size(game, DIMENSION - line - 1, column);

            if (5 - line == picked_line && column == picked_column && picked_owner != NO_PLAYER)
            {
                // Checking which player is currently holding the piece, to print it according to his color
                render_selected_piece(ren, env, picked_size, line, column);
            }
            else if (line == hovered_line && column == hovered_column && env->current_state == MID_SELECT_SPOT)
            {
                // Render the hovered sprite
                render_hovered_piece(ren, env, piece, line, column);
            }
            else
            {
                // Render the regular piece icon if no piece is selected
                render_piece(ren, env, piece, line, column);
            }
        }
    }

    if (env->current_state == INI_SELECT_SPOT)
    {

        int line;

        if (env->current_player == SOUTH_P)
        {
            line = 0;
        }
        else
        {
            line = 5;
        }

        for (int i = 0; i < DIMENSION; i++)
        {
            if (get_piece_size(env->game, line, i) == NONE)
            {
                render_shadow(env, ren, DIMENSION - line - 1, i);
            }
        }
    }
    else if (env->current_state == INI_SELECT_SIZE)
    {
        int width = SCREEN_WIDTH / 2;
        int height = SCREEN_HEIGHT / 3;

        int mid_width = width / 2;
        int mid_height = SCREEN_HEIGHT / 3 - height / 2;

        SDL_Rect rect = {width / 2, height / 2, width, height};

        printf("%d, %d, %d, %d\n", rect.x, rect.y, rect.w, rect.h);

        //SDL_SetSurfaceAlphaMod(ren, 150);
        SDL_SetRenderDrawColor(ren, TEXT_COLOR, 1);

        int gap = 20;
        int piece_width = (width - gap * 3) / 3;

        for (int i = 1; i <= NB_SIZE; i++)
        {
            SDL_Rect crop = {0, (i - 1) * 245, 245, 245};
            SDL_Rect position = {mid_width - (piece_width * 1.5 + gap + piece_width * i), mid_height, piece_width, piece_width};

            if (position.x <= mouse_x && mouse_x <= position.x + position.w && position.y <= mouse_y && mouse_y <= position.x + position.h)
            {
                SDL_RenderDrawRect(ren, &position);
            }

            if (nb_pieces_available(env->game, i, env->current_player) > 0)
            {
                crop.x = env->normal_piece;
            }
            else
            {
                crop.x = env->gray_piece;
            }

            SDL_RenderCopy(ren, env->tilemap, &crop, &position);
        }
        /*
         * --> x = mid - (piece_w * (nb_pieces * 0.5) + gap * ((nb_piece - 1) * 0.5)) + piece_w * i 
        */
        SDL_RenderFillRect(ren, &rect);
    }

    /*
    
    else if (env->current_state == INI_SELECT_SPOT)
    {
        if (env->current_player == NORTH_P && env)
        place_piece();
        //env->clicked_line;
        //env->clicked_column;
    }
    
    */

    if (env->err_showtime > 0)
    {
        env->err_showtime--;
        display_message(env, ren, env->err_msg, true);
    }

    if (env->info_showtime > 0)
    {
        env->info_showtime--;
        display_message(env, ren, env->info_msg, false);
    }

    // SDL_RenderCopy(ren, env->background, NULL, &drect);
}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e)
{

    if (e->type == SDL_QUIT)
    {
        return true;
    }
    else if (e->type == SDL_MOUSEBUTTONUP) //SDL_GetMouseState / https://wiki.libsdl.org/SDL_GetMouseState
    {
        SDL_Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        env->clicked_line = 5 - (mouse.y - OFFSET) / CELL_SIZE;
        env->clicked_column = (mouse.x - OFFSET) / CELL_SIZE;

        handle_click(env, env->clicked_line, env->clicked_column);
    }
    else if (e->type == SDL_KEYDOWN)
    {
        if (e->key.keysym.sym == SDLK_ESCAPE)
        {
            return true;
        }
    }

    /* PUT YOUR CODE HERE TO PROCESS EVENTS */

    return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env)
{
    /* PUT YOUR CODE HERE TO CLEAN MEMORY */

    SDL_DestroyTexture(env->background);

    free(env);
}

/* **************************************************************** */
