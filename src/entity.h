#ifndef ROM_ENTITY_H
#define ROM_ENTITY_H

#include "init.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "defs.h"
#include "stdio.h"
#include "string.h"

typedef struct Entity_Data {
    char *name;
    int id;
    int x;
    int y;
    SDL_Texture *texture;
} Entity;

extern Entity *initEntity(char *name, int x, int y);
extern void moveEntity(Entity *entity, int mx, int my);

#endif // ROM_ENTITY_H
