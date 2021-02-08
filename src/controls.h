#ifndef ROM_CONTROLS_H
#define ROM_CONTROLS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "defs.h"
#include "entity.h"

extern Game_Display game_display;
extern Game_State game_state;
extern SDL_bool initializing;
extern Entity *player;
extern int window_width;
extern int window_height;

extern void handleInput(void);

#endif // ROM_CONTROLS_H
