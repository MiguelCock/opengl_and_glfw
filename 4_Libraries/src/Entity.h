#include "Math2D.h"

struct Entity {
    struct Point3 center;
    int pointsAmount;
    struct Point3* p3List;
    int conections;
    struct Point3 *conectionsList;
};

struct Entity* entCreate();

void entFree(struct Entity* ent);