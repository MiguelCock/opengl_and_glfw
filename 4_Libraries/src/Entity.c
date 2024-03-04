#include "Entity.h"
#include <stdlib.h>

struct Entity* entCreate() {
    struct Entity* ent = (struct Entity*)malloc(sizeof(struct Entity*));

    return ent;
}

void entFree(struct Entity* ent) {
    free(ent->center);
    free(ent->p3List);
    free(ent->conectionsList);
    free(ent);
}