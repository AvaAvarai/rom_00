#include "SDL2/SDL.h"

#define WINDOW_TITLE "Rom_00"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define LOAD_SCREEN_PATH "loading.png"

typedef struct Game_Displays {
    SDL_Renderer *renderer;
    SDL_Window *window;
} Game_Display;
