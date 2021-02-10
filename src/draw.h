#ifndef ROM_DRAW_H
#define ROM_DRAW_H

#include "defs.h"
#include "entity.h"

extern Game_Display game_display;
extern Game_State game_state;
extern SDL_bool initializing;
extern Entity *player;
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

extern SDL_Texture *tiles[3];

extern int map[100][100];

extern void renderFrame(void);
extern void clearScreen(SDL_Color);
extern void renderMenu(void);
extern void renderLoading(void);
extern void renderPaused(void);
extern void renderGame(void);

#endif // ROM_DRAW_H
