#ifndef ROM_INIT_H
#define ROM_INIT_H

#include "defs.h"

extern void initSDL(void);
extern void cleanup(int exitcode);
extern void loadTextures(void);

extern SDL_Texture *loadSym(char sym, SDL_Color color);

extern int window_width;
extern int window_height;

extern SDL_Texture *menu_background;
extern SDL_Rect menu_rect;
extern SDL_Texture *loading_image;
extern SDL_Rect load_rect;
extern SDL_Texture *paused_image;
extern SDL_Rect paused_rect;
extern SDL_Surface *start_text_surface;
extern SDL_Texture *start_text_texture;
extern SDL_Rect start_text_rect;

extern TTF_Font *title_font;
extern TTF_Font *game_font;
extern SDL_Surface *play_sym_surface;
extern SDL_Texture *play_sym_texture;

extern SDL_Texture *tiles[3];
extern SDL_Texture *tile_image;
extern SDL_Texture *tile2_image;

extern Game_Display game_display;

#endif // ROM_INIT_H
