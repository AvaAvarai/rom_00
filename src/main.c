#include "main.h"

int main(int argc, char* argv[]) {

    memset(&game_display, 0, sizeof(Game_Display));

    SDL_Texture *menu_background;
    int menu_w, menu_h;

    SDL_Texture *start_text_img;
    int start_w, start_h;

    SDL_Texture *loading_image;
    int load_w, load_h;

    initGameDisplays();

    menu_background = IMG_LoadTexture(game_display.renderer, MENU_BACKGROUND_PATH);
    SDL_QueryTexture(menu_background, NULL, NULL, &menu_w, &menu_h);
    SDL_Rect menu_texr;
    menu_texr.x = WINDOW_WIDTH/2 - menu_w/2;
    menu_texr.y = WINDOW_HEIGHT/2 - menu_h/2;
    menu_texr.w = menu_w;
    menu_texr.h = menu_h;

    start_text_img = IMG_LoadTexture(game_display.renderer, MENU_START_TEXT_PATH);
    SDL_QueryTexture(start_text_img, NULL, NULL, &start_w, &start_h);
    SDL_Rect start_texr;
    start_texr.x = WINDOW_WIDTH/2 - start_w/2;
    start_texr.y = WINDOW_HEIGHT/2 - start_h/2;
    start_texr.w = start_w;
    start_texr.h = start_h;
    
    loading_image = IMG_LoadTexture(game_display.renderer, LOAD_SCREEN_PATH);
    SDL_QueryTexture(loading_image, NULL, NULL, &load_w, &load_h);
    SDL_Rect load_texr;
    load_texr.x = WINDOW_WIDTH/2 - load_w/2;
    load_texr.y = WINDOW_HEIGHT/2 - load_h/2;
    load_texr.w = load_w;
    load_texr.h = load_h;

    int game_state = MAIN_MENU;
    while (game_state != EXITING) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    game_state = EXITING;
                    SDL_RenderCopy(game_display.renderer, loading_image, NULL, &load_texr);
                    SDL_RenderPresent(game_display.renderer);
                    SDL_Delay(1000);
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(game_display.renderer, 0, 255, 255, 255); // Set background color -- Cyan
        SDL_RenderClear(game_display.renderer);

        SDL_RenderCopy(game_display.renderer, menu_background, NULL, &menu_texr);
        SDL_RenderCopy(game_display.renderer, start_text_img, NULL, &start_texr);

        SDL_RenderPresent(game_display.renderer);
    }

    SDL_DestroyTexture(menu_background);
    destroyGameDisplays();

    SDL_Quit();
    return 0;
}
