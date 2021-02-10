#include "defs.h"
#include "init.h"
#include "draw.h"
#include "input.h"
#include "entity.h"

// Game Window Sizes
int window_width = WINDOW_WIDTH;
int window_height = WINDOW_HEIGHT;

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

// TODO: Add map loading class
int map[100][100];

int main(int argc, char* argv[]) {
    // Initialization
    (void)argc; (void)argv;
    memset(&game_display, 0, sizeof(Game_Display));
    memset(&player, 0, sizeof(Entity));
    memset(&game_state, 0, sizeof(Game_State));
    memset(&initializing, 0, sizeof(initializing));
    
    memset(&map, 0, sizeof(map));
    map[50][50] = 1;

    initializing = SDL_TRUE;
    game_state = MAIN_MENU;
    
    initSDL();
    loadTextures();
    SDL_GetWindowSize(game_display.window, &window_width, &window_height);
    player = initEntity("Player", 50, 50);

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
    cleanup(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

// END OF MAIN
