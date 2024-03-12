#include "Math2D.h"

struct Entity
{
    struct Point3 center;
    int pointsAmount;
    struct Point3 *p3List;
    int conections;
    int *conectionsList;
};

struct Entity *entCreate();

void entFree(struct Entity *ent);

void entDraw(struct Entity * ent);

struct Entity* entReadFile();