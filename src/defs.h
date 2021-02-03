#ifndef ROM_DEFS_H
#define ROM_DEFS_H

#include "SDL2/SDL.h"

// Window and Tile Constants
#define WINDOW_TITLE  "Rom_00"
#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480
#define TILE_WIDTH    64
#define TILE_HEIGHT   32

// Data Structures
typedef struct Game_Displays {
    SDL_Renderer *renderer;
    SDL_Window *window;
} Game_Display;

#endif // ROM_DEFS_H
