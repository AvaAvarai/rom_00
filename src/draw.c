#include "draw.h"

extern void renderFrame(void) {
    clearScreen((SDL_Color)CYAN_COLOR);
    switch (game_state) {
        case MAIN_MENU:
            renderMenu();
            break;
        case LOADING:
            renderLoading();
            break;
        case PAUSED:
            renderPaused();
            break;
        case PLAYING:
            renderGame();
            break;
        default:
            break;
    }
    SDL_RenderPresent(game_display.renderer);
}

extern void renderMenu(void) {
    SDL_RenderCopy(game_display.renderer, menu_background, NULL, &menu_rect);
    SDL_RenderCopy(game_display.renderer, start_text_texture, NULL, &start_text_rect);
}

extern void renderLoading(void) {
    SDL_RenderCopy(game_display.renderer, loading_image, NULL, &load_rect);
}

extern void renderPaused(void) {
    SDL_RenderCopy(game_display.renderer, paused_image, NULL, &paused_rect);
}

extern void renderGame(void) { // TODO: Reapproach render loop?
    int player_sight = 4;

    for (int rows = -player_sight; rows <= player_sight; rows++) {
        for (int cols = -player_sight; cols <= player_sight; cols++) {
            // Screen Coordinate Selection
            int new_tile_x = (rows - cols) * (TILE_WIDTH / 2) + window_width / 2 - TILE_WIDTH / 2;
            int new_tile_y = (rows + cols) * (TILE_HEIGHT / 2) + window_height / 2 - TILE_HEIGHT / 2;
            SDL_Rect tile_rect = {new_tile_x, new_tile_y, TILE_WIDTH, TILE_HEIGHT};
            // Skip out of screen bounds
            if (new_tile_x < 0 - TILE_WIDTH || new_tile_y < 0 - TILE_HEIGHT) continue;
            if (new_tile_x >= window_width && new_tile_y >= window_height) continue;
            // Debug logging WARN: WILL LAG.
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_F1]) {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Placing Tile -> r: %d c: %d x: %d y: %d", rows, cols, new_tile_x, new_tile_y);
            }
            SDL_RenderCopy(game_display.renderer, tiles[0], NULL, &tile_rect);
        }
    }
    // Draw Player
    // SDL_RenderCopy(game_display.renderer, player->texture, NULL, &(const SDL_Rect){window_width/2 - TILE_WIDTH/4, window_height/2 - TILE_HEIGHT/2, 32, 32});
    if (initializing) initializing = SDL_FALSE; // Done initializing after first renderGame call.
}

extern void clearScreen(SDL_Color clear_color) {
    SDL_SetRenderDrawColor(game_display.renderer, clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    SDL_RenderClear(game_display.renderer);
}
