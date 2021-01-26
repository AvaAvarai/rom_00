#include "init.h"

void initGameDisplays(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    game_display.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!game_display.window) {
        printf("Failed to initialize window: %s\n", SDL_GetError());
        exit(1);
    }
    game_display.renderer = SDL_CreateRenderer(game_display.window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!game_display.renderer) {
        printf("Failed to initialize renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void destroyGameDisplays(void) {
    SDL_DestroyRenderer(game_display.renderer);
    SDL_DestroyWindow(game_display.window);
}
