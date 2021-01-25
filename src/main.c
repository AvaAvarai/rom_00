#include "main.h"

int main(int argc, char* argv[]) {

    memset(&game_display, 0, sizeof(Game_Display));

    SDL_Texture *menu_background;
    int w, h;

    initGameDisplays();

    menu_background = IMG_LoadTexture(game_display.renderer, LOAD_SCREEN_PATH);
    SDL_QueryTexture(menu_background, NULL, NULL, &w, &h);
    SDL_Rect texr; texr.x = WINDOW_WIDTH/2 - w/2; texr.y = WINDOW_HEIGHT/2 - h/2; texr.w = w; texr.h = h;
    
    int game_state = MAIN_MENU;
    while (game_state != EXITING) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    game_state = EXITING;
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(game_display.renderer, 0, 255, 255, 255); // Set background color -- Cyan
        SDL_RenderClear(game_display.renderer);

        SDL_RenderCopy(game_display.renderer, menu_background, NULL, &texr);

        SDL_RenderPresent(game_display.renderer);
    }

    SDL_DestroyTexture(menu_background);
    destroyGameDisplays();

    SDL_Quit();
    return 0;
}
