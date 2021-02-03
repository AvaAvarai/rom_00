#ifndef ROM_INIT_H
#define ROM_INIT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "defs.h"

extern void initSDL(Game_Display *game_display);
extern void cleanup(Game_Display *game_display, int exitcode);

#endif // ROM_INIT_H
