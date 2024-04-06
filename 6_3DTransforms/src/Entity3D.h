#include "Math3D.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGTH 720

typedef struct
{
    int x;
    int y;
} conection;

typedef struct
{
    int pointsAmount;
    vec4 *p4List;
    int conections;
    conection *conectionsList;
    //double angle;
    vec4 center;
} Entity;

void entFree(Entity *ent);

void entDraw(Entity *ent, mat4 *projection);

Entity *entReadFile(char *filename);

void entTransform(Entity *ent, mat4 *m4);

void entTrueTrans(Entity *ent, mat4 *m4);