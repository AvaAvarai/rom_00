#include "common.h"

int main(int argc, char* argv[]) {

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *img;
    int w, h;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        WIDTH,                               // width, in pixels
        HEIGHT,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    img = IMG_LoadTexture(renderer, LOAD_SCREEN_PATH);
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_Rect texr; texr.x = WIDTH/2 - w/2; texr.y = HEIGHT/2 - h/2; texr.w = w; texr.h = h;

    if (window == NULL) {
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

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, img, NULL, &texr);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
