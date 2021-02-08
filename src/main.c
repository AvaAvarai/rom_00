#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "stdint.h"
#include "init.h"
#include "defs.h"
#include "entity.h"

// Game Data Structure Declarations
Game_Display game_display;
Entity *player;
Game_State game_state;
SDL_bool initializing;

// Menu Asset Declarations
SDL_Texture *menu_background;
SDL_Rect menu_rect;
SDL_Texture *loading_image;
SDL_Rect load_rect;
SDL_Texture *paused_image;
SDL_Rect paused_rect;
SDL_Surface *start_text_surface;
SDL_Texture *start_text_texture;
SDL_Rect start_text_rect;

// Font Asset Declarations
TTF_Font *title_font;
TTF_Font *game_font;

// Game Asset Declarations
SDL_Texture *tiles[3];
SDL_Texture *tile_image;
SDL_Texture *tile2_image;

// Function declarations TODO: Add rendering class, Add controls class
static void renderFrame(void); // Entry-point function to rendering module.
static void clearScreen(SDL_Color);
static void renderMenu(void);
static void renderLoading(void);
static void renderPaused(void);
static void renderGame(void);
static void handleInput(void); // Entry-point function to controls module.

int main(int argc, char* argv[]) {
    // Initialization
    (void)argc; (void)argv;
    memset(&game_display, 0, sizeof(Game_Display));
    memset(&player, 0, sizeof(Entity));
    memset(&game_state, 0, sizeof(Game_State));
    memset(&initializing, 0, sizeof(initializing));
    initializing = SDL_TRUE;
    game_state = MAIN_MENU;
    initSDL(&game_display);
    loadTextures(&game_display);
    player = initEntity("Player", 5, 5);
    Uint32 fps_lasttime = SDL_GetTicks();
    Uint32 fps_current = 0;
    Uint32 fps_frames = 0;

    while (game_state != EXITING) {

        // Display current FPS Calculation
        char new_title[strlen(WINDOW_TITLE) + 20];
        sprintf(new_title, "%s -- %dFPS", WINDOW_TITLE, fps_current);
        SDL_SetWindowTitle(game_display.window, new_title);
        
        // FPS Calculation
        fps_frames++;
        if (fps_lasttime < SDL_GetTicks() - 1000) {
            fps_lasttime = SDL_GetTicks();
            fps_current = fps_frames;
            fps_frames = 0;
        }

        // Input
        handleInput();

        // Rendering
        renderFrame();
    } // END MAIN LOOP

    // Shutdown Routines
    // TODO: Access/Destroy textures through looping/programmatic process.
    SDL_DestroyTexture(tiles[0]);
    SDL_DestroyTexture(tiles[1]);
    SDL_DestroyTexture(tiles[2]);
    SDL_DestroyTexture(menu_background);
    SDL_DestroyTexture(loading_image);
    SDL_DestroyTexture(paused_image);
    SDL_DestroyTexture(start_text_texture);
    SDL_DestroyTexture(player->texture);
    free(player);
    cleanup(&game_display, EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

// END OF MAIN -- TODO: Move functions to following modules. (1. Rendering 2. Input 3. Init | Load | Cleanup | Closing)

// TODO: Move handleInput to control class
static void handleInput(void) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: // TODO: CLEANUP Menu-traversing logic
                if (event.key.keysym.sym == SDLK_ESCAPE) { // Exiting game--
                    clearScreen((SDL_Color)CYAN_COLOR);
                    if (game_state == PLAYING) game_state = PAUSED;
                    else if (game_state == MAIN_MENU) game_state = EXITING;
                    else if (game_state == PAUSED || game_state == LOADING) game_state = MAIN_MENU;
                }
                else if (game_state == MAIN_MENU || game_state == LOADING) { // Entering game--
                    clearScreen((SDL_Color)CYAN_COLOR);
                    initializing = SDL_TRUE;
                    game_state++;
                }
                else if (game_state == PAUSED) {
                    clearScreen((SDL_Color)CYAN_COLOR);
                    game_state = PLAYING;
                } 
                if (game_state == PLAYING) { // During game--
                    switch (event.key.keysym.sym) {
                        case SDLK_a:
                        case SDLK_KP_7:
                            moveEntity(player, 1, -1);
                            break;
                        case SDLK_w:
                        case SDLK_KP_9:
                            moveEntity(player, 1, 1);
                            break;
                        case SDLK_s:
                        case SDLK_KP_1:
                            moveEntity(player, -1, -1);
                            break;
                        case SDLK_d:
                        case SDLK_KP_3:
                            moveEntity(player, -1, 1);
                            break;
                        case SDLK_r:
                            player->x = 0;
                            player->y = 0;
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
}

// TODO: Move rendering funcs to render class
static void renderFrame(void) {
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

static void renderMenu(void) {
    SDL_RenderCopy(game_display.renderer, menu_background, NULL, &menu_rect);
    SDL_RenderCopy(game_display.renderer, start_text_texture, NULL, &start_text_rect);
}

static void renderLoading(void) {
    SDL_RenderCopy(game_display.renderer, loading_image, NULL, &load_rect);
}

static void renderPaused(void) {
    SDL_RenderCopy(game_display.renderer, paused_image, NULL, &paused_rect);
}

static void renderGame(void) {
    int player_sight = 5;

    for (int rows = player->x - player_sight; rows < player->x + player_sight; rows++) {
        for (int cols = player->y - player_sight; cols < player->y + player_sight; cols++) {

            // Screen Coordinate Selection
            int new_tile_x = (rows - cols) * (TILE_WIDTH / 2) + WINDOW_WIDTH / 2 - TILE_WIDTH / 2;
            int new_tile_y = (rows + cols) * (TILE_HEIGHT / 2) + WINDOW_HEIGHT / 4 - TILE_HEIGHT / 2;
            SDL_Rect tile_rect = {new_tile_x, new_tile_y, TILE_WIDTH, TILE_HEIGHT};
            
            SDL_RenderCopy(game_display.renderer, tiles[0], NULL, &tile_rect);
           
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Placing Tile -> x: %d y: %d", new_tile_x, new_tile_y);
        }
    }
    // Draw Player
    SDL_RenderCopy(game_display.renderer, player->texture, NULL, &(const SDL_Rect){WINDOW_WIDTH/2 - TILE_WIDTH/8, WINDOW_HEIGHT/2 - TILE_HEIGHT/2, 32, 32});
    if (initializing) initializing = SDL_FALSE; // Done initializing after first renderGame call.
}

static void clearScreen(SDL_Color clear_color) {
    SDL_SetRenderDrawColor(game_display.renderer, clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    SDL_RenderClear(game_display.renderer);
}
