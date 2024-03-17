#include "Math2D.h"

struct Entity
{
    struct Point3 center;
    int pointsAmount;
    struct Point3 *p3List;
    int conections;
    int *conectionsList;
    double angle;
};

struct Entity *entCreate();

void entFree(struct Entity *ent);

void entDraw(struct Entity * ent);

struct Entity* entReadFile();

void entTransform(struct Entity *ent,struct Matrix3x3 *m3);