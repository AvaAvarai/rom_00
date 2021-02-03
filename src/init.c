#include "init.h"

extern void initSDL(Game_Display *game_display) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize SDL: %s\n", SDL_GetError());
        cleanup(game_display, EXIT_FAILURE);
    }
    game_display->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!game_display->window) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize window: %s\n", SDL_GetError());
        cleanup(game_display, EXIT_FAILURE);
    }
    game_display->renderer = SDL_CreateRenderer(game_display->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!game_display->renderer) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize renderer: %s\n", SDL_GetError());
        cleanup(game_display, EXIT_FAILURE);
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize PNG loading libraries: %s\n", IMG_GetError());
        cleanup(game_display, EXIT_FAILURE);
    }
    if (TTF_Init() == -1) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize TTF loading libraries: %s\n", TTF_GetError());
        cleanup(game_display, EXIT_FAILURE);
    }
}

extern void cleanup(Game_Display *game_display, int exitcode) {
    SDL_DestroyRenderer(game_display->renderer);
    SDL_DestroyWindow(game_display->window);

    // TODO: Access/Destroy textures through looping/programmatic process.
    // MOVED TEXTURE DESTRUCTION TO MAIN LOOP TEMPORARILY | PUT BACK HERE@!

    IMG_Quit();
    TTF_Quit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    exit(exitcode);
}
