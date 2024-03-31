#include "Math2D.h"

typedef struct
{
    int x;
    int y;
} conection;

typedef struct
{
    int pointsAmount;
    Point3 *p3List;
    int conections;
    conection *conectionsList;
    double angle;
    Point3 center;
} Entity;

Entity *entCreate();

void entFree(Entity *ent);

void entDraw(Entity * ent);

Entity* entReadFile(char *filename);

void entTransform(Entity *ent, Matrix3x3 *m3);