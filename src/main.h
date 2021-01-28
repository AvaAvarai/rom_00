#include "common.h"

Game_Display game_display;

static void initSDL(void);
static void clearScreen(void);
static void renderFrame(void);
static void cleanup(int exitcode);
