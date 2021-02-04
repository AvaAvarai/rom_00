#ifndef ROM_INIT_H
#define ROM_INIT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "defs.h"

extern void initSDL(Game_Display *game_display);
extern void cleanup(Game_Display *game_display, int exitcode);
extern void loadTextures(Game_Display *game_display);

// Menu Asset Declarations
extern SDL_Texture *menu_background;
extern SDL_Rect menu_rect;
extern SDL_Texture *loading_image;
extern SDL_Rect load_rect;
extern SDL_Texture *paused_image;
extern SDL_Rect paused_rect;
extern SDL_Surface *start_text_surface;
extern SDL_Texture *start_text_texture;
extern SDL_Rect start_text_rect;

// Font Asset Declarations
extern TTF_Font *title_font;
extern TTF_Font *game_font;
extern SDL_Surface *play_sym_surface;
extern SDL_Texture *play_sym_texture;

// Game Asset Declarations
extern SDL_Texture *tiles[3];
extern SDL_Texture *tile_image;
extern SDL_Texture *tile2_image;

extern Player player;

#endif // ROM_INIT_H
