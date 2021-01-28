#include "main.h"

int map[9][9] = { // Mock Game-World space--
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

SDL_Texture *tiles[3];

int main(int argc, char* argv[]) {
    // Startup Routines --
    memset(&game_display, 0, sizeof(Game_Display));
    game_display.starting = SDL_TRUE;

    initSDL();

    // Load Menu Assets--
    SDL_Texture *menu_background = IMG_LoadTexture(game_display.renderer, MENU_BACKGROUND_PATH);;
    int img_w = 0; int img_h = 0;
    SDL_QueryTexture(menu_background, NULL, NULL, &img_w, &img_h);
    SDL_Rect menu_rect = {WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    SDL_Texture *loading_image = IMG_LoadTexture(game_display.renderer, LOAD_SCREEN_PATH);
    SDL_QueryTexture(loading_image, NULL, NULL, &img_w, &img_h);
    SDL_Rect load_rect = {WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    SDL_Texture *paused_image = IMG_LoadTexture(game_display.renderer, PAUSE_SCREEN_PATH);
    SDL_QueryTexture(paused_image, NULL, NULL, &img_w, &img_h);
    SDL_Rect paused_rect = {WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    // Load Tiles--
    SDL_Texture *tile_image = IMG_LoadTexture(game_display.renderer, TILE_PATH);
    SDL_Texture *tile2_image = IMG_LoadTexture(game_display.renderer, TILE2_PATH);
    tiles[0] = tile_image;
    tiles[1] = tile2_image;
    
    // Load Fonts--
    TTF_Font *title_font = TTF_OpenFont(FONT_PATH, 32);
    TTF_Font *game_font = TTF_OpenFont(FONT_PATH, 22);
    
    SDL_Color white_color = {255, 255, 255, 255};

    SDL_Surface *start_text_surface = TTF_RenderText_Solid(title_font, "Press Any Key To Start.", white_color);
    SDL_Texture *start_text_texture = SDL_CreateTextureFromSurface(game_display.renderer, start_text_surface);
    SDL_QueryTexture(start_text_texture, NULL, NULL, &img_w, &img_h);
    SDL_Rect start_text_rect = {WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    SDL_Surface *play_sym_surface = TTF_RenderText_Solid(game_font, "@", white_color);
    SDL_Texture *play_sym_texture = SDL_CreateTextureFromSurface(game_display.renderer, play_sym_surface);
    tiles[2] = play_sym_texture;

    game_display.player.play_sym_w = 0;
    game_display.player.play_sym_h = 0;
    SDL_QueryTexture(play_sym_texture, NULL, NULL, &game_display.player.play_sym_w, &game_display.player.play_sym_h);
    game_display.player.play_sym_rect = (SDL_Rect){WINDOW_WIDTH/2 - TILE_WIDTH/8, WINDOW_HEIGHT/2 - TILE_HEIGHT/2, game_display.player.play_sym_w, game_display.player.play_sym_h};
    int play_x = 0; int play_y = 0; // Mock Player Location--

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
                        game_display.starting = SDL_TRUE;
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
                                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Moved -> x: %d y: %d", play_x, play_y);
                                break;
                            case SDLK_w:
                            case SDLK_KP_9:
                                play_x++;
                                play_y++;
                                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Moved -> x: %d y: %d", play_x, play_y);
                                break;
                            case SDLK_s:
                            case SDLK_KP_1:
                                play_x--;
                                play_y--;
                                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Moved -> x: %d y: %d", play_x, play_y);
                                break;
                            case SDLK_d:
                            case SDLK_KP_3:
                                play_x++;
                                play_y--;
                                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Moved -> x: %d y: %d", play_x, play_y);
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
                renderFrame();
                break;
            default:
                break;
        }
        SDL_RenderPresent(game_display.renderer);
    }

    // Shutdown Routines --
    SDL_DestroyTexture(menu_background);
    SDL_DestroyTexture(loading_image);
    TTF_CloseFont(title_font);
    TTF_CloseFont(game_font);
    SDL_DestroyTexture(start_text_texture);
    SDL_FreeSurface(start_text_surface);
    SDL_DestroyTexture(tile_image);
    SDL_DestroyTexture(tile2_image);

    cleanup(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

static void renderFrame(void) {
    for (size_t i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
        for (size_t q = 0; q < sizeof(map[0]) / sizeof(int); q++) {
            // Screen Coordinate Selection--
            int new_tile_x = (i - q) * (TILE_WIDTH / 2) + WINDOW_WIDTH / 2 - TILE_WIDTH / 2;
            int new_tile_y = (i + q) * (TILE_HEIGHT / 2) + WINDOW_HEIGHT / 4 - TILE_HEIGHT / 2 ;
            SDL_Rect tile_rect = {new_tile_x, new_tile_y, TILE_WIDTH, TILE_HEIGHT};
            // Tile Selection--
            if (map[q][i] == 0) SDL_RenderCopy(game_display.renderer, tiles[0], NULL, &tile_rect);
            else SDL_RenderCopy(game_display.renderer, tiles[1], NULL, &tile_rect);
            // Debug Logging--
            if (game_display.starting) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Placing Tile -> x: %d y: %d", new_tile_x, new_tile_y);
            if (game_display.starting) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "map[%d][%d] -> %d", (int)i, (int)q, map[i][q]);              
        }
    }
    SDL_RenderCopy(game_display.renderer, tiles[2], NULL, &game_display.player.play_sym_rect);
    if (game_display.starting) game_display.starting = SDL_FALSE;
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
