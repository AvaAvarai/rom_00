#ifndef ROM_DEFS_H
#define ROM_DEFS_H

#include "SDL2/SDL.h"

// Window and Tile Constants
#define WINDOW_TITLE  "Rom_00"
#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480
#define TILE_WIDTH    64
#define TILE_HEIGHT   32

#define WHITE_COLOR {255, 255, 255, SDL_ALPHA_OPAQUE}
#define CYAN_COLOR  {0, 255, 255, SDL_ALPHA_OPAQUE}

// Asset Paths
#define MENU_BACKGROUND_PATH "assets/menu.png"
#define LOAD_SCREEN_PATH     "assets/loading.png"
#define PAUSE_SCREEN_PATH    "assets/paused.png"
#define TILE_PATH            "assets/test_tile.png"
#define TILE2_PATH           "assets/tile2.png"
#define FONT_PATH            "assets/dungeon-grunge.ttf"

typedef struct Game_Displays {
    SDL_Renderer *renderer;
    SDL_Window *window;
} Game_Display;

typedef enum Game_States {
    EXITING   = -1,
    MAIN_MENU =  0,
    LOADING   =  1,
    PLAYING   =  2,
    PAUSED    =  3
} Game_State;

#endif // ROM_DEFS_H
