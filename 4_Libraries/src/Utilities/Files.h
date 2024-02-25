struct Point
{
    int x;
    int y;
};

struct Object
{
    int vertex;
    struct Point *vertexList;
    int conections;
    struct Point *conectionsList;
};

void freeObject(struct Object *obj);

struct Object *readFile();

void drawObject(struct Object *obj);