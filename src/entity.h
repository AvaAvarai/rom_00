#ifndef ROM_ENTITY_H
#define ROM_ENTITY_H

#include "defs.h"

typedef struct Entity_Data {
    char *name;
    int uid; // Not implemented
    int x;
    int y;
    SDL_Texture *texture;
} Entity;

extern Entity *initEntity(char *name, int x, int y);
extern void moveEntity(Entity *entity, int mx, int my);

#endif // ROM_ENTITY_H
