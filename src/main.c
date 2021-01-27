#include "main.h"

int main(int argc, char* argv[]) {
    // Startup Routines --
    memset(&game_display, 0, sizeof(Game_Display));

    initSDL();

    SDL_Texture *menu_background = IMG_LoadTexture(game_display.renderer, MENU_BACKGROUND_PATH);;
    int menu_w = 0; int menu_h = 0;
    SDL_QueryTexture(menu_background, NULL, NULL, &menu_w, &menu_h);
    SDL_Rect menu_rect = {WINDOW_WIDTH/2 - menu_w/2, WINDOW_HEIGHT/2 - menu_h/2, menu_w, menu_h};

    SDL_Texture *loading_image = IMG_LoadTexture(game_display.renderer, LOAD_SCREEN_PATH);
    int load_w = 0; int load_h = 0;
    SDL_QueryTexture(loading_image, NULL, NULL, &load_w, &load_h);
    SDL_Rect load_rect = {WINDOW_WIDTH/2 - load_w/2, WINDOW_HEIGHT/2 - load_h/2, load_w, load_h};

    SDL_Texture *paused_image = IMG_LoadTexture(game_display.renderer, PAUSE_SCREEN_PATH);
    int paused_w = 0; int paused_h = 0;
    SDL_QueryTexture(paused_image, NULL, NULL, &paused_w, &paused_h);
    SDL_Rect paused_rect = {WINDOW_WIDTH/2 - paused_w/2, WINDOW_HEIGHT/2 - paused_h/2, paused_w, paused_h};

    SDL_Texture *tile_image = IMG_LoadTexture(game_display.renderer, TILE_PATH);;
    int tile_w = 0; int tile_h = 0;
    SDL_QueryTexture(tile_image, NULL, NULL, &tile_w, &tile_h);

    int center_x = WINDOW_WIDTH/2 - tile_w/2;
    int center_y = WINDOW_HEIGHT/2 - tile_h/2;
    
    SDL_Rect tile_rect = {center_x, center_y, tile_w, tile_h};
    SDL_Rect tile_rect_left = {center_x - tile_w/2, center_y - tile_h/2, tile_w, tile_h};
    SDL_Rect tile_rect_fwd = {center_x + tile_w/2, center_y - tile_h/2, tile_w, tile_h};
    SDL_Rect tile_rect_right = {center_x + tile_w/2, center_y + tile_h/2, tile_w, tile_h};
    SDL_Rect tile_rect_back = {center_x - tile_w/2, center_y + tile_h/2, tile_w, tile_h};

    TTF_Font *font = TTF_OpenFont(FONT_PATH, 22);
    SDL_Color white_color = {255, 255, 255, 255};

    SDL_Surface *start_text_surface = TTF_RenderText_Solid(font, "Press Any Key To Start Prototype.", white_color);
    SDL_Texture *start_text_texture = SDL_CreateTextureFromSurface(game_display.renderer, start_text_surface);
    int start_text_w = 0; int start_text_h = 0;
    SDL_QueryTexture(start_text_texture, NULL, NULL, &start_text_w, &start_text_h);
    SDL_Rect start_text_rect = {WINDOW_WIDTH/2 - start_text_w/2, WINDOW_HEIGHT/2 - start_text_h/2, start_text_w, start_text_h};

    SDL_Surface *play_sym_surface = TTF_RenderText_Solid(font, "@", white_color);
    SDL_Texture *play_sym_texture = SDL_CreateTextureFromSurface(game_display.renderer, play_sym_surface);
    int play_sym_w = 0; int play_sym_h = 0;
    SDL_QueryTexture(play_sym_texture, NULL, NULL, &play_sym_w, &play_sym_h);
    SDL_Rect play_sym_rect = {WINDOW_WIDTH/2 - play_sym_w/2, WINDOW_HEIGHT/2 - play_sym_h/2, play_sym_w, play_sym_h};

    int play_x = 0; int play_y = 0;

    // Runtime Routines --
    Uint32 fps_lasttime = SDL_GetTicks();
    Uint32 fps_current = 0;
    Uint32 fps_frames = 0;
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Start play_x: %d play_y: %d", play_x, play_y);
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
                case SDL_KEYDOWN: // TODO: CLEANUP Menu-traversing logic
                    if (event.key.keysym.sym == SDLK_ESCAPE) { // Exiting game--
                        clearScreen();
                        if (game_state == PLAYING) game_state = PAUSED;
                        else if (game_state == MAIN_MENU) game_state = EXITING;
                        else if (game_state == PAUSED || game_state == LOADING) game_state = MAIN_MENU;
                        continue;
                    }
                    if (game_state == MAIN_MENU || game_state == LOADING) { // Entering game--
                        clearScreen();
                        game_state++;
                        continue;
                    }
                    else if (game_state == PAUSED) {
                        clearScreen();
                        game_state = PLAYING;
                        continue;
                    } 
                    if (game_state == PLAYING) { // During game--
                        switch (event.key.keysym.sym) {
                            case SDLK_a:
                            case SDLK_KP_7:
                                play_x--;
                                play_y++;
                                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "New play_x: %d play_y: %d", play_x, play_y);
                                break;
                            case SDLK_w:
                            case SDLK_KP_9:
                                play_x++;
                                play_y++;
                                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "New play_x: %d play_y: %d", play_x, play_y);
                                break;
                            case SDLK_s:
                            case SDLK_KP_1:
                                play_x--;
                                play_y--;
                                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "New play_x: %d play_y: %d", play_x, play_y);
                                break;
                            case SDLK_d:
                            case SDLK_KP_3:
                                play_x++;
                                play_y--;
                                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "New play_x: %d play_y: %d", play_x, play_y);
                                break;
                            default:
                                break;
                        }
                    }
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
                SDL_RenderCopy(game_display.renderer, menu_background, NULL, &menu_rect);
                SDL_RenderCopy(game_display.renderer, start_text_texture, NULL, &start_text_rect);
                break;
            case LOADING:
                SDL_RenderCopy(game_display.renderer, loading_image, NULL, &load_rect);
                break;
            case PAUSED:
                SDL_RenderCopy(game_display.renderer, paused_image, NULL, &paused_rect);
                break;
            case PLAYING:
                SDL_RenderCopy(game_display.renderer, tile_image, NULL, &tile_rect_left);
                SDL_RenderCopy(game_display.renderer, tile_image, NULL, &tile_rect_fwd);
                SDL_RenderCopy(game_display.renderer, tile_image, NULL, &tile_rect);
                SDL_RenderCopy(game_display.renderer, tile_image, NULL, &tile_rect_right);
                SDL_RenderCopy(game_display.renderer, tile_image, NULL, &tile_rect_back);
                SDL_RenderCopy(game_display.renderer, play_sym_texture, NULL, &play_sym_rect);
                break;
            default:
                break;
        }
        SDL_RenderPresent(game_display.renderer);
    }

    // Shutdown Routines --
    SDL_DestroyTexture(menu_background);
    SDL_DestroyTexture(loading_image);
    TTF_CloseFont(font);
    SDL_DestroyTexture(start_text_texture);
    SDL_FreeSurface(start_text_surface);

    cleanup(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

static void initSDL(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize SDL: %s\n", SDL_GetError());
        cleanup(EXIT_FAILURE);
    }
    game_display.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!game_display.window) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize window: %s\n", SDL_GetError());
        cleanup(EXIT_FAILURE);
    }
    game_display.renderer = SDL_CreateRenderer(game_display.window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!game_display.renderer) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize renderer: %s\n", SDL_GetError());
        cleanup(EXIT_FAILURE);
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize PNG loading libraries: %s\n", IMG_GetError());
        cleanup(EXIT_FAILURE);
    }
    if (TTF_Init() == -1) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize TTF loading libraries: %s\n", TTF_GetError());
        cleanup(EXIT_FAILURE);
    }
}

static void clearScreen(void) {
    SDL_SetRenderDrawColor(game_display.renderer, 0, 255, 255, 255); // Set background color -- Cyan
    SDL_RenderClear(game_display.renderer);
}

static void cleanup(int exitcode) {
    SDL_DestroyRenderer(game_display.renderer);
    SDL_DestroyWindow(game_display.window);

    IMG_Quit();
    TTF_Quit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    exit(exitcode);
}
