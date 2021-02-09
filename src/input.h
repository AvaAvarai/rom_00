#ifndef ROM_INPUT_H
#define ROM_INPUT_H

#include "defs.h"
#include "entity.h"

extern Game_Display game_display;
extern Game_State game_state;
extern SDL_bool initializing;
extern Entity *player;
extern int window_width;
extern int window_height;

extern void handleInput(void);

#endif // ROM_INPUT_H
