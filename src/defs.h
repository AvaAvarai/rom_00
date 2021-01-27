#include "SDL2/SDL.h"

#define WINDOW_TITLE "Rom_00"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define MENU_BACKGROUND_PATH "assets/menu.png"
#define LOAD_SCREEN_PATH "assets/loading.png"
#define PAUSE_SCREEN_PATH "assets/paused.png"
#define TILE_PATH "assets/tile.png"

#define FONT_PATH "assets/dungeon-grunge.ttf"

typedef struct Game_Displays {
    SDL_Renderer *renderer;
    SDL_Window *window;
} Game_Display;

typedef enum Game_States {
    EXITING = -1,
    MAIN_MENU = 0,
    LOADING = 1,
    PLAYING = 2,
    PAUSED = 3
} Game_State;
