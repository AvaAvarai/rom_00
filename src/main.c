#include "main.h"

int main(int argc, char* argv[]) {

    // Startup Routines --

    memset(&game_display, 0, sizeof(Game_Display));

    initSDL();

    SDL_Texture *menu_background = IMG_LoadTexture(game_display.renderer, MENU_BACKGROUND_PATH);;
    int menu_w, menu_h;
    SDL_QueryTexture(menu_background, NULL, NULL, &menu_w, &menu_h);
    SDL_Rect menu_texr;
    menu_texr.x = WINDOW_WIDTH/2 - menu_w/2;
    menu_texr.y = WINDOW_HEIGHT/2 - menu_h/2;
    menu_texr.w = menu_w;
    menu_texr.h = menu_h;

    SDL_Texture *start_text_img = IMG_LoadTexture(game_display.renderer, MENU_START_TEXT_PATH);
    int start_w, start_h;
    SDL_QueryTexture(start_text_img, NULL, NULL, &start_w, &start_h);
    SDL_Rect start_texr;
    start_texr.x = WINDOW_WIDTH/2 - start_w/2;
    start_texr.y = WINDOW_HEIGHT/2 - start_h/2;
    start_texr.w = start_w;
    start_texr.h = start_h;

    SDL_Texture *loading_image = IMG_LoadTexture(game_display.renderer, LOAD_SCREEN_PATH);
    int load_w, load_h;
    SDL_QueryTexture(loading_image, NULL, NULL, &load_w, &load_h);
    SDL_Rect load_texr;
    load_texr.x = WINDOW_WIDTH/2 - load_w/2;
    load_texr.y = WINDOW_HEIGHT/2 - load_h/2;
    load_texr.w = load_w;
    load_texr.h = load_h;

    SDL_SetRenderDrawColor(game_display.renderer, 0, 255, 255, 255); // Set background color -- Cyan
    SDL_RenderClear(game_display.renderer);

    // Runtime Routines --

    Uint32 fps_lasttime = SDL_GetTicks();
    Uint32 fps_current;
    Uint32 fps_frames = 0;

    Game_State game_state = MAIN_MENU;
    while (game_state != EXITING) {
        // FPS Calc --
        char new_title[strlen(WINDOW_TITLE) + 20];
        sprintf(new_title, "%s -- %dFPS", WINDOW_TITLE, fps_current);
        SDL_SetWindowTitle(game_display.window, new_title);
        fps_frames++;
        if (fps_lasttime < SDL_GetTicks() - 1000) {
            fps_lasttime = SDL_GetTicks();
            fps_current = fps_frames;
            fps_frames = 0;
        }

        // Input --
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (game_state == MAIN_MENU) game_state = PLAYING;
                    if (event.key.keysym.sym == SDLK_ESCAPE) game_state = EXITING;
                    break;
                case SDL_QUIT:
                    game_state = EXITING;
                    break;
                default:
                    break;
            }
        }
        
        // Rendering --
        switch (game_state) {
            case MAIN_MENU:
                SDL_RenderCopy(game_display.renderer, menu_background, NULL, &menu_texr);
                SDL_RenderCopy(game_display.renderer, start_text_img, NULL, &start_texr);
                break;
            case PLAYING:
                SDL_RenderCopy(game_display.renderer, loading_image, NULL, &load_texr);
                break;
            default:
                break;
        }
        SDL_RenderPresent(game_display.renderer);
    }

    // Shutdown Routines --

    SDL_DestroyTexture(menu_background);
    SDL_DestroyTexture(start_text_img);
    SDL_DestroyTexture(loading_image);
    
    SDL_DestroyRenderer(game_display.renderer);
    SDL_DestroyWindow(game_display.window);

    cleanup(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

static void initSDL(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initialize SDL: %s\n", SDL_GetError());
        cleanup(EXIT_FAILURE);
    }
    game_display.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!game_display.window) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initialize window: %s\n", SDL_GetError());
        cleanup(EXIT_FAILURE);
    }
    game_display.renderer = SDL_CreateRenderer(game_display.window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!game_display.renderer) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initialize renderer: %s\n", SDL_GetError());
        cleanup(EXIT_FAILURE);
    }
}

static void cleanup(int exitcode) {
    IMG_Quit();
    SDL_Quit();
    exit(exitcode);
}
