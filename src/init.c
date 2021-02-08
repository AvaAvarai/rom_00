#include "init.h"
#include "stdio.h"

// TODO: Streamline without game_display parameter
extern void initSDL(Game_Display *game_display) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize SDL: %s\n", SDL_GetError());
        cleanup(game_display, EXIT_FAILURE);
    }
    game_display->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
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
    free(game_display);
    exit(exitcode);
}

extern void loadTextures(Game_Display *game_display) {
    // Load Menu Assets
    menu_background = IMG_LoadTexture(game_display->renderer, MENU_BACKGROUND_PATH);
    int img_w = 0; int img_h = 0;
    SDL_QueryTexture(menu_background, NULL, NULL, &img_w, &img_h);
    menu_rect = (SDL_Rect){WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    loading_image = IMG_LoadTexture(game_display->renderer, LOAD_SCREEN_PATH);
    SDL_QueryTexture(loading_image, NULL, NULL, &img_w, &img_h);
    load_rect = (SDL_Rect){WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    paused_image = IMG_LoadTexture(game_display->renderer, PAUSE_SCREEN_PATH);
    SDL_QueryTexture(paused_image, NULL, NULL, &img_w, &img_h);
    paused_rect = (SDL_Rect){WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    // Load Tiles
    tile_image = IMG_LoadTexture(game_display->renderer, TILE_PATH);
    tile2_image = IMG_LoadTexture(game_display->renderer, TILE2_PATH);
    tiles[0] = tile_image;
    tiles[1] = tile2_image;
    
    // Load Fonts
    title_font = TTF_OpenFont(FONT_PATH, 32);
    game_font = TTF_OpenFont(FONT_PATH, 22);

    // Use Fonts
    start_text_surface = TTF_RenderText_Solid(title_font, "Press Any Key To Start.", (SDL_Color)WHITE_COLOR);
    start_text_texture = SDL_CreateTextureFromSurface(game_display->renderer, start_text_surface);
    SDL_QueryTexture(start_text_texture, NULL, NULL, &img_w, &img_h);
    start_text_rect = (SDL_Rect){WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};
}

extern SDL_Texture *loadSym(char sym) {
    SDL_Surface *out_surface = TTF_RenderGlyph_Solid(game_font, sym, (SDL_Color)WHITE_COLOR);
    return SDL_CreateTextureFromSurface(game_display.renderer, out_surface);
}
