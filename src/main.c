#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "stdint.h"

// Function declerations
static void loadTextures(void);
static void initSDL(void);
static void clearScreen(void);
static void renderMenu(void);
static void renderLoading(void);
static void renderPaused(void);
static void handleInput(void);
static void renderGame(void);
static void cleanup(int exitcode);

// Window and Tile Constants
#define WINDOW_TITLE  "Rom_00"
#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480
#define TILE_WIDTH    64
#define TILE_HEIGHT   32

// Asset Paths
#define MENU_BACKGROUND_PATH "assets/menu.png"
#define LOAD_SCREEN_PATH     "assets/loading.png"
#define PAUSE_SCREEN_PATH    "assets/paused.png"
#define TILE_PATH            "assets/tile.png"
#define TILE2_PATH           "assets/tile2.png"
#define FONT_PATH            "assets/dungeon-grunge.ttf"

// Data Structures
typedef struct Game_Displays {
    SDL_Renderer *renderer;
    SDL_Window *window;
} Game_Display;

typedef struct Players {
    int8_t player_x;
    int8_t player_y;
    SDL_Rect play_sym_rect;
} Player;

typedef enum Game_States {
    EXITING = -1,
    MAIN_MENU = 0,
    LOADING = 1,
    PLAYING = 2,
    PAUSED = 3
} Game_State;

// Game Data Structure Declarations
Game_Display game_display;
Player player;
Game_State game_state;
SDL_bool initializing;

// Color Definitions
SDL_Color white_color = {255, 255, 255, SDL_ALPHA_OPAQUE};
SDL_Color cyan_color = {0, 255, 255, SDL_ALPHA_OPAQUE};

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
SDL_Surface *play_sym_surface;
SDL_Texture *play_sym_texture;

// Game Asset Declarations
SDL_Texture *tiles[3];
SDL_Texture *tile_image;
SDL_Texture *tile2_image;

// Mock Game Data
int map[9][9] = {
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

int main(int argc, char* argv[]) {
    
    // Initialization
    (void)argc; (void)argv;
    memset(&game_display, 0, sizeof(Game_Display));
    memset(&player, 0, sizeof(Player));
    memset(&game_state, 0, sizeof(Game_State));
    memset(&initializing, 0, sizeof(initializing));
    initializing = SDL_TRUE;
    player.player_x = 0; player.player_y = 0;
    game_state = MAIN_MENU;

    initSDL();
    loadTextures();

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

    // Shutdown Routines
    cleanup(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

// END OF MAIN -- TODO: Move functions to following modules. (1. Rendering 2. Input 3. Init | Load | Cleanup | Closing)

static void handleInput(void) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: // TODO: CLEANUP Menu-traversing logic
                if (event.key.keysym.sym == SDLK_ESCAPE) { // Exiting game--
                    clearScreen();
                    if (game_state == PLAYING) game_state = PAUSED;
                    else if (game_state == MAIN_MENU) game_state = EXITING;
                    else if (game_state == PAUSED || game_state == LOADING) game_state = MAIN_MENU;
                }
                else if (game_state == MAIN_MENU || game_state == LOADING) { // Entering game--
                    clearScreen();
                    initializing = SDL_TRUE;
                    game_state++;
                }
                else if (game_state == PAUSED) {
                    clearScreen();
                    game_state = PLAYING;
                } 
                if (game_state == PLAYING) { // During game--
                    switch (event.key.keysym.sym) {
                        case SDLK_a:
                        case SDLK_KP_7:
                            player.player_x--;
                            player.player_y++;
                            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Moved -> x: %d y: %d", player.player_x, player.player_y);
                            break;
                        case SDLK_w:
                        case SDLK_KP_9:
                            player.player_x++;
                            player.player_y++;
                            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Moved -> x: %d y: %d", player.player_x, player.player_y);
                            break;
                        case SDLK_s:
                        case SDLK_KP_1:
                            player.player_x--;
                            player.player_y--;
                            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Moved -> x: %d y: %d", player.player_x, player.player_y);
                            break;
                        case SDLK_d:
                        case SDLK_KP_3:
                            player.player_x++;
                            player.player_y--;
                            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player Moved -> x: %d y: %d", player.player_x, player.player_y);
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
    for (size_t i = 0; i < sizeof(map) / sizeof(map[0]); i++) { // Rows--
        for (size_t q = 0; q < sizeof(map[0]) / sizeof(int); q++) { // Cols--
            // Screen Coordinate Selection--
            int new_tile_x = (i - q) * (TILE_WIDTH / 2) + WINDOW_WIDTH / 2 - TILE_WIDTH / 2;
            int new_tile_y = (i + q) * (TILE_HEIGHT / 2) + WINDOW_HEIGHT / 4 - TILE_HEIGHT / 2 ;
            SDL_Rect tile_rect = {new_tile_x, new_tile_y, TILE_WIDTH, TILE_HEIGHT};
            // Tile Selection--
            if (map[q][i] == 0) SDL_RenderCopy(game_display.renderer, tiles[0], NULL, &tile_rect);
            else SDL_RenderCopy(game_display.renderer, tiles[1], NULL, &tile_rect);
            // Debug Logging--
            if (initializing) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Placing Tile -> x: %d y: %d", new_tile_x, new_tile_y);
            if (initializing) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "map[%d][%d] -> %d", (int)i, (int)q, map[i][q]);              
        }
    }
    SDL_RenderCopy(game_display.renderer, tiles[2], NULL, &player.play_sym_rect);
    if (initializing) initializing = SDL_FALSE;
}

static void initSDL(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize SDL: %s\n", SDL_GetError());
        cleanup(EXIT_FAILURE);
    }
    game_display.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!game_display.window) {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, "Failed to initialize window: %s\n", SDL_GetError());
        cleanup(EXIT_FAILURE);
    }
    game_display.renderer = SDL_CreateRenderer(game_display.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

static void loadTextures(void) {
    // Load Menu Assets
    menu_background = IMG_LoadTexture(game_display.renderer, MENU_BACKGROUND_PATH);
    int img_w = 0; int img_h = 0;
    SDL_QueryTexture(menu_background, NULL, NULL, &img_w, &img_h);
    menu_rect = (SDL_Rect){WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    loading_image = IMG_LoadTexture(game_display.renderer, LOAD_SCREEN_PATH);
    SDL_QueryTexture(loading_image, NULL, NULL, &img_w, &img_h);
    load_rect = (SDL_Rect){WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    paused_image = IMG_LoadTexture(game_display.renderer, PAUSE_SCREEN_PATH);
    SDL_QueryTexture(paused_image, NULL, NULL, &img_w, &img_h);
    paused_rect = (SDL_Rect){WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    // Load Tiles
    tile_image = IMG_LoadTexture(game_display.renderer, TILE_PATH);
    tile2_image = IMG_LoadTexture(game_display.renderer, TILE2_PATH);
    tiles[0] = tile_image;
    tiles[1] = tile2_image;
    
    // Load Fonts
    title_font = TTF_OpenFont(FONT_PATH, 32);
    game_font = TTF_OpenFont(FONT_PATH, 22);

    // Use Fonts
    start_text_surface = TTF_RenderText_Solid(title_font, "Press Any Key To Start.", white_color);
    start_text_texture = SDL_CreateTextureFromSurface(game_display.renderer, start_text_surface);
    SDL_QueryTexture(start_text_texture, NULL, NULL, &img_w, &img_h);
    start_text_rect = (SDL_Rect){WINDOW_WIDTH/2 - img_w/2, WINDOW_HEIGHT/2 - img_h/2, img_w, img_h};

    play_sym_surface = TTF_RenderText_Solid(game_font, "@", white_color);
    play_sym_texture = SDL_CreateTextureFromSurface(game_display.renderer, play_sym_surface);
    tiles[2] = play_sym_texture;

    player.play_sym_rect = (SDL_Rect){WINDOW_WIDTH/2 - TILE_WIDTH/8, WINDOW_HEIGHT/2 - TILE_HEIGHT/2, 32, 32};
}

static void clearScreen(void) {
    SDL_SetRenderDrawColor(game_display.renderer, 0, 255, 255, SDL_ALPHA_OPAQUE); // Set background color -- Cyan
    SDL_RenderClear(game_display.renderer);
}

static void cleanup(int exitcode) {
    SDL_DestroyRenderer(game_display.renderer);
    SDL_DestroyWindow(game_display.window);

    // TODO: Access/Destroy textures through looping/programmatic process.
    SDL_DestroyTexture(tiles[0]);
    SDL_DestroyTexture(tiles[1]);
    SDL_DestroyTexture(tiles[2]);
    SDL_DestroyTexture(menu_background);
    SDL_DestroyTexture(loading_image);
    SDL_DestroyTexture(paused_image);
    SDL_DestroyTexture(start_text_texture);

    IMG_Quit();
    TTF_Quit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    exit(exitcode);
}
