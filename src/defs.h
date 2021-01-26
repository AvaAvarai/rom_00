#include "SDL2/SDL.h"

#define WINDOW_TITLE "Rom_00"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define MENU_BACKGROUND_PATH "assets/menu.png"
#define MENU_START_TEXT_PATH "assets/start_text.png"
#define LOAD_SCREEN_PATH "assets/loading.png"

typedef struct Game_Displays {
    SDL_Renderer *renderer;
    SDL_Window *window;
} Game_Display;

typedef enum Game_States {
    EXITING = -1,
    MAIN_MENU = 0,
    PLAYING = 1
} Game_State;
