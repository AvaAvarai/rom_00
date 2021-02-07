#include "entity.h"

// WIP Entity class

extern Entity *initEntity(char *name, int x, int y) {
   Entity *out = malloc(sizeof(Entity));
   out->name = name;
   out->x = x;
   out->y = y;
   if (strcmp(name, "Player") == 0) {
       out->texture = loadSym('@');
   }
   return out;
}

extern void moveEntity(Entity *entity, int mx, int my) {
    entity->x += mx;
    entity->y += my;
}
