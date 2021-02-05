#include "entity.h"
#include "init.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "defs.h"
#include "stdio.h"
#include "string.h"

// WIP Entity class

struct Entity {
    char *name;
    int id;
    int x;
    int y;
    SDL_Texture *texture;
};

extern struct Entity *initEntity(char *name, int x, int y) {
   struct Entity *out = malloc(sizeof(struct Entity));
   out->name = name;
   out->x = x;
   out->y = y;
   if (strcmp(name, "Player") == 0) {
       out->texture = loadSym('@');
   }
   return out;
}
