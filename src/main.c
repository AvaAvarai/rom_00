#include "common.h"

int main(int argc, char* argv[]) {

    Game_Display game_display;
    memset(&game_display, 0, sizeof(Game_Display));

    SDL_Texture *img;
    int w, h;

    SDL_Init(SDL_INIT_VIDEO);

    game_display.window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    game_display.renderer = SDL_CreateRenderer(game_display.window, -1, SDL_RENDERER_ACCELERATED);

    img = IMG_LoadTexture(game_display.renderer, LOAD_SCREEN_PATH);
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_Rect texr; texr.x = WINDOW_WIDTH/2 - w/2; texr.y = WINDOW_HEIGHT/2 - h/2; texr.w = w; texr.h = h;

    if (game_display.window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    running = 0;
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(game_display.renderer, 0, 255, 255, 255);
        SDL_RenderClear(game_display.renderer);

        SDL_RenderCopy(game_display.renderer, img, NULL, &texr);

        SDL_RenderPresent(game_display.renderer);
    }

    SDL_DestroyRenderer(game_display.renderer);

    SDL_DestroyWindow(game_display.window);

    SDL_Quit();
    return 0;
}
