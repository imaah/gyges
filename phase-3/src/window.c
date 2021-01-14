#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // required to load transparent texture from PNG

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

#include "window.h"
#include "board.h"
#include "game.h"

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[])
{
    SDL_SetWindowResizable(win, SDL_FALSE);
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

    env->swap_icon = IMG_LoadTexture(ren, SWAP_ICON);
    if (!env->swap_icon)
        ERROR("IMG_LoadTexture: %s\n", SWAP_ICON);

    env->continue_icon = IMG_LoadTexture(ren, CONTINUE_ICON);
    if (!env->swap_icon)
        ERROR("IMG_LoadTexture: %s\n", CONTINUE_ICON);

    SDL_Surface *icon = IMG_Load("assets/icon.png");

    SDL_SetWindowIcon(win, icon);

    // Game variables
    env->game = new_game();
    env->current_player = SOUTH_P;
    env->current_state = INI_SELECT_SPOT;

    env->clicked_line = -1;
    env->clicked_column = -1;

    env->selected_column = -1;

    env->err_msg = malloc(sizeof(char) * 255);
    env->info_msg = malloc(sizeof(char) * 255);

    env->err_showtime = 0;
    env->info_showtime = 0;

    env->placed_piece = 0;

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

void display_info(Env *env, SDL_Renderer *ren, char *message_content, bool is_error)
{
    SDL_Surface *broadcastMessage;

    if (is_error)
    {
        SDL_Color color = {RED_COLOR};
        broadcastMessage = TTF_RenderUTF8_Blended(env->font, message_content, color);
    }
    else
    {
        SDL_Color color = {GREEN_COLOR};
        broadcastMessage = TTF_RenderUTF8_Blended(env->font, message_content, color);
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(ren, broadcastMessage);

    // The numbers in this formula were found by trying. We chose the best variables according to what we though was the best result
    SDL_Rect background = {SCREEN_WIDTH / 2 - 5 - strlen(message_content) * (FONT_SIZE / 20), SCREEN_HEIGHT / 4 - FONT_SIZE / 6, strlen(message_content) * (FONT_SIZE / 10) + 10, FONT_SIZE / 4.3};

    // Adapting the y axis if the message is not an error
    if (is_error != true)
    {
        background.y = SCREEN_HEIGHT / 4 + FONT_SIZE / 6 * 2;
    }

    SDL_SetRenderDrawColor(ren, GRAY_COLOR, 128);

    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(ren, &background);
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_INVALID);

    SDL_RenderCopy(ren, message, NULL, &background);
}

void show_text(Env *env, SDL_Renderer *ren, char *text, SDL_Rect rect, SDL_Color color)
{
    SDL_Surface *text_surface = TTF_RenderUTF8_Blended(env->font, text, color);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(ren, text_surface);

    SDL_RenderCopy(ren, text_texture, NULL, &rect);
}

void render_piece(SDL_Renderer *ren, Env *env, size piece_size, int piece_position, float line, float column)
{
    SDL_Rect rect;
    set_piece_rect(&rect, line, column);
    if (piece_size != NONE)
    {
        SDL_Rect crop = {piece_position, (piece_size - 1) * 245, 245, 245};
        SDL_RenderCopy(ren, env->tilemap, &crop, &rect);
    }
}

void render_normal_piece(SDL_Renderer *ren, Env *env, size piece_size, float line, float column)
{
    render_piece(ren, env, piece_size, env->normal_piece, line, column);
}

void render_selected_piece(SDL_Renderer *ren, Env *env, size piece_size, float line, float column)
{
    render_piece(ren, env, piece_size, env->selected_piece, line, column);
}

void render_hovered_piece(SDL_Renderer *ren, Env *env, size piece_size, float line, float column)
{
    render_piece(ren, env, piece_size, env->hovered_piece, line, column);
}

void render_gray_piece(SDL_Renderer *ren, Env *env, size piece_size, float line, float column)
{
    render_piece(ren, env, piece_size, env->gray_piece, line, column);
}

void render_shadow(Env *env, SDL_Renderer *ren, float line, float column)
{
    SDL_Rect rect;
    set_piece_rect(&rect, line, column);
    SDL_RenderCopy(ren, env->tilemap, &env->shadow_rect, &rect);
}

void render(SDL_Window *win, SDL_Renderer *ren, Env *env)
{
    SDL_RenderCopy(ren, env->background, NULL, NULL);
    board game = env->game;

    int picked_line = picked_piece_line(game);
    int picked_column = picked_piece_column(game);
    player picked_owner = picked_piece_owner(game);
    size picked_size = picked_piece_size(game);

    size south_goal_size = get_goal_piece(game, SOUTH_P);
    size north_goal_size = get_goal_piece(game, NORTH_P);

    render_normal_piece(ren, env, south_goal_size, 6, 2.5);
    render_normal_piece(ren, env, north_goal_size, -1, 2.5);

    // Getting the mouse position to render a different piece sprite
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    int hovered_line = (mouse_y - OFFSET) / CELL_SIZE;
    int hovered_column = (mouse_x - OFFSET) / CELL_SIZE;

    int southmost = southmost_occupied_line(env->game);
    int northmost = northmost_occupied_line(env->game);

    for (int line = 0; line < DIMENSION; line++)
    {
        // Looping through columns
        for (int column = 0; column < DIMENSION; column++)
        {
            // Getting which piece to place in these coordinates
            size piece = get_piece_size(game, DIMENSION - line - 1, column);

            if (env->current_state == MID_SWAP_PIECE && piece == NONE)
            {
                render_shadow(env, ren, line, column);
            }
            else if (env->current_state == MID_SELECT_PIECE && ((env->current_player == NORTH_P && 5 - line != northmost) || (env->current_player == SOUTH_P && 5 - line != southmost)))
            {
                render_gray_piece(ren, env, piece, line, column);
            }
            else if (5 - line == picked_line && column == picked_column && picked_owner != NO_PLAYER && env->current_state != VICTORY)
            {
                // Checking which player is currently holding the piece, to print it according to his color
                render_selected_piece(ren, env, picked_size, line, column);
            }
            else if (line == hovered_line && column == hovered_column && env->current_state == MID_SELECT_PIECE)
            {
                // Render the hovered sprite
                render_hovered_piece(ren, env, piece, line, column);
            }
            else
            {
                // Render the regular piece icon if no piece is selected
                render_normal_piece(ren, env, piece, line, column);
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

        int padding = 10;
        int mid_width = width / 2;
        int mid_height = SCREEN_HEIGHT / 2 - height / 2;

        SDL_Rect rect = {SCREEN_WIDTH / 2 - width / 2, SCREEN_HEIGHT / 2 - height / 2, width, height};

        //SDL_SetSurfaceAlphaMod(ren, 150);
        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren, GRAY_COLOR, 190);
        SDL_RenderFillRect(ren, &rect);
        SDL_Color color = {0, 0, 0, 255};

        SDL_Rect title_rect = {SCREEN_WIDTH / 2 - mid_width + padding, SCREEN_HEIGHT / 2 - height / 2 + padding, width - padding * 2, FONT_SIZE / 2};

        show_text(env, ren, "Choix de la taille de la pièce", title_rect, color);

        int gap = 20;
        int piece_width = ((width - padding * 2) - gap * 2) / 3;
        int y_offset = 60;
        for (int i = 1; i <= NB_SIZE; i++)
        {
            SDL_Rect crop = {0, (i - 1) * 245, 245, 245};
            SDL_Rect position = {padding + mid_width - (piece_width * 1.5 + gap) + piece_width * (i + .5) + gap * i, mid_height + padding / 2 + y_offset, piece_width, piece_width};
            SDL_Rect around = {position.x - padding / 2, position.y - padding / 2, position.w + padding, position.h + gap + FONT_SIZE / 2.5};

            if (around.x <= mouse_x && mouse_x <= around.x + around.w && around.y <= mouse_y && mouse_y <= around.y + around.h)
            {
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
                SDL_RenderFillRect(ren, &around);
            }

            SDL_Rect text_pos = {position.x, position.y + piece_width + gap, piece_width, FONT_SIZE / 5};
            int pieces_available = nb_pieces_available(env->game, i, env->current_player);

            SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);

            if (pieces_available > 0)
            {
                crop.x = env->normal_piece;

                if (pieces_available == 1)
                {
                    show_text(env, ren, "1 restante", text_pos, color);
                }
                else if (pieces_available == 2)
                {
                    show_text(env, ren, "2 restantes", text_pos, color);
                }
                else
                {
                    show_text(env, ren, "3 restantes", text_pos, color);
                }
            }
            else
            {
                crop.x = env->gray_piece;
                show_text(env, ren, "0 restante", text_pos, color);
            }

            SDL_RenderCopy(ren, env->tilemap, &crop, &position);
            SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        }
        /*
         * --> x = mid - (piece_w * (nb_pieces * 0.5) + gap * ((nb_piece - 1) * 0.5)) + piece_w * i 
         */
    }
    else if (env->current_state == MID_SELECT_ACTION)
    {
        int width = SCREEN_WIDTH / 2;
        int height = SCREEN_HEIGHT / 3;

        int padding = 20;
        int mid_width = width / 2;
        int mid_height = SCREEN_HEIGHT / 2 - height / 2;

        SDL_Rect rect = {SCREEN_WIDTH / 2 - width / 2, SCREEN_HEIGHT / 2 - height / 2, width, height};

        //SDL_SetSurfaceAlphaMod(ren, 150);
        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren, GRAY_COLOR, 190);
        SDL_RenderFillRect(ren, &rect);
        SDL_Color color = {0, 0, 0, 255};

        SDL_Rect title_rect = {SCREEN_WIDTH / 2 - mid_width + padding, SCREEN_HEIGHT / 2 - height / 2, width - padding * 2, FONT_SIZE / 2};

        show_text(env, ren, "Choix de l'action", title_rect, color);

        int gap = 20;
        int piece_width = ((width - padding * 2) - gap) / 2;
        int y_offset = 30;

        for (int i = 1; i < 3; i++)
        {
            SDL_Rect position = {padding + mid_width - (piece_width * 1.5 + gap) + piece_width * (i + .5) + gap * i, mid_height + padding + y_offset, piece_width, piece_width};
            SDL_Rect around = {position.x - padding / 2, position.y - padding / 2, position.w + padding, position.h + FONT_SIZE / 2.5};

            SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

            if (around.x <= mouse_x && mouse_x <= around.x + around.w && around.y <= mouse_y && mouse_y <= around.y + around.h)
            {
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 200);
                SDL_RenderFillRect(ren, &around);
            }

            SDL_Rect text_pos = {position.x, position.y + piece_width, piece_width, FONT_SIZE / 4};

            SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);

            if (i == 1)
            {
                show_text(env, ren, "Continuer", text_pos, color);
                SDL_RenderCopy(ren, env->continue_icon, NULL, &position);
            }
            else
            {
                show_text(env, ren, "Echanger", text_pos, color);
                SDL_RenderCopy(ren, env->swap_icon, NULL, &position);
            }
        }
    }
    else if (env->current_state == MID_MOVE_PIECE)
    {
        SDL_Rect remaining_moves_box = {0, 0, 150, FONT_SIZE / 3.4};

        if (env->current_player == NORTH_P) {
            remaining_moves_box.x = SCREEN_WIDTH - OFFSET - 150;
            remaining_moves_box.y = OFFSET - FONT_SIZE / 3.4 - 7;
        } else {
            remaining_moves_box.x = OFFSET;
            remaining_moves_box.y = OFFSET + 6 * CELL_SIZE;
        }

        int remaining_moves = movement_left(env->game);

        char rm_s[30];

        sprintf(rm_s, "%d", remaining_moves);

        SDL_Color color = {GREEN_COLOR};

        if (remaining_moves == 1) {
            remaining_moves_box.w -= 7; // To get the same width as the plurial string
            
            show_text(env, ren, strcat(rm_s, " déplacement restant"), remaining_moves_box, color);
        } else {
            show_text(env, ren, strcat(rm_s, " déplacements restants"), remaining_moves_box, color);
        }

        for (int i = 0; i < 5; i++)
        {
            if (is_move_possible(env->game, i))
            {

                if (i == GOAL)
                {
                    if (env->current_player == NORTH_P)
                    {
                        render_shadow(env, ren, 6, 2.5);
                    }
                    else
                    {
                        render_shadow(env, ren, -1, 2.5);
                    }
                }
                else
                {
                    int *movement = move(i);
                    render_shadow(env, ren, 5 - picked_line - movement[0], picked_column + movement[1]);
                }
            }
        }
    }
    else if (env->current_state == VICTORY)
    {
        SDL_Color color = {0, 0, 0, 255};
        SDL_Rect text = {200, 300 - FONT_SIZE / 4, 200, FONT_SIZE / 1.5};

        SDL_Rect rect = {SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT / 2 - FONT_SIZE / 4 - 5, 260, FONT_SIZE / 1.5 + 10};

        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

        SDL_SetRenderDrawColor(ren, BLUE_COLOR, 150);
        SDL_RenderFillRect(ren, &rect);

        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);

        if (get_winner(env->game) == NORTH_P)
        {
            show_text(env, ren, "Bravo joueur nord !", rect, color);
        }
        else if (get_winner(env->game) == SOUTH_P)
        {
            show_text(env, ren, "Bravo joueur sud !", text, color);
        }
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
        display_info(env, ren, env->err_msg, true);
    }

    if (env->info_showtime > 0)
    {
        env->info_showtime--;
        display_info(env, ren, env->info_msg, false);
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

        int width = SCREEN_WIDTH / 2;
        int height = SCREEN_HEIGHT / 3;
        int mid_width = width / 2;
        int mid_height = SCREEN_HEIGHT / 2 - height / 2;

        if (env->current_state == INI_SELECT_SIZE)
        {
            int padding = 10;
            int gap = 20;
            int piece_width = ((width - padding * 2) - gap * 2) / 3;
            int y_offset = 60;

            for (int i = 0; i <= NB_SIZE; i++)
            {
                SDL_Rect position = {
                    padding + mid_width - (piece_width * 1.5 + gap) + piece_width * (i + .5) + gap * i,
                    mid_height + padding / 2 + y_offset,
                    piece_width, 
                    piece_width
                };
                SDL_Rect around = {
                    position.x - padding / 2, 
                    position.y - padding / 2, 
                    position.w + padding, 
                    position.h + gap + FONT_SIZE / 2.5
                };

                if (
                    around.x <= mouse.x &&
                    mouse.x <= around.x + around.w && 
                    around.y <= mouse.y && 
                    mouse.y <= around.y + around.h
                )
                {
                    ini_select_size(env, i);
                    break;
                }
            }

            return false;
        }
        else if (env->current_state == MID_SELECT_ACTION)
        {
            int gap = 20;
            int padding = 20;
            int piece_width = ((width - padding * 2) - gap) / 2;
            int y_offset = 30;

            for (int i = 1; i < 3; i++)
            {
                SDL_Rect position = {padding + mid_width - (piece_width * 1.5 + gap) + piece_width * (i + .5) + gap * i, mid_height + padding + y_offset, piece_width, piece_width};
                SDL_Rect around = {position.x - padding / 2, position.y - padding / 2, position.w + padding, position.h + FONT_SIZE / 2.5};

                if (around.x <= mouse.x && mouse.x <= around.x + around.w && around.y <= mouse.y && mouse.y <= around.y + around.h)
                {
                    if (i == 1)
                    {
                        mid_select_action(env, CONTINUE);
                    }
                    else
                    {
                        mid_select_action(env, SWAP);
                    }
                    break;
                }
            }

            return false;
        }
        else if (env->current_state == VICTORY)
        {
            destroy_game(env->game);
            env->game = new_game();
            env->current_state = INI_SELECT_SPOT;
            env->current_player = SOUTH_P;
            env->placed_piece = 0;

            return false;
        }

        if (env->clicked_line == picked_piece_line(env->game) && env->clicked_column == picked_piece_column(env->game))
        {
            if (env->current_state == MID_MOVE_PIECE)
            {
                if (env->moves_made == 0)
                {
                    cancel_movement(env->game);
                    env->current_state = MID_SELECT_PIECE;
                }
                else
                {
                    cancel_step(env->game);
                    env->moves_made--;
                }

                return false;
            }
            else if (env->current_state == MID_SWAP_PIECE)
            {
                env->current_state = MID_SELECT_ACTION;
            }
        }

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
