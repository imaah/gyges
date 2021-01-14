#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>   // required to use TTF fonts

#include "board.h"

enum game_state_e {
    INI_SELECT_SPOT,
    INI_SELECT_SIZE,
    MID_SELECT_PIECE,
    MID_MOVE_PIECE,
    MID_SELECT_ACTION,
    MID_SWAP_PIECE,

    VICTORY
};

typedef enum game_state_e game_state;

struct Env_t
{
    SDL_Texture *background;

    SDL_Texture *tilemap;
    SDL_Texture *swap_icon;
    SDL_Texture *continue_icon;

    TTF_Font *font;

    int gray_piece;
    int selected_piece;
    int normal_piece;
    int hovered_piece;

    SDL_Rect shadow_rect;

    board game;
    player current_player;

    int selected_column;

    game_state current_state;


    int clicked_line;
    int clicked_column;

    int hovered_line;
    int hovered_column;

    char *err_msg;
    int err_showtime;

    char *info_msg;
    int info_showtime;
    int moves_made;

    int placed_piece;
    /* PUT YOUR VARIABLES HERE */
};

typedef struct Env_t Env;