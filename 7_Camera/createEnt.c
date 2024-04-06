#include "src/Include.h"
#include <string.h>

int main()
{

    int err;

    //====================WRITING THE FILES====================

    FILE *file;
    char filename[] = "entity.bin";

    // Created the bin file
    file = fopen(filename, "wb");

    // Check if file opened successfully
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file '%s'\n", filename);
        return 1;
    }

    // save the amount of points in the file
    int points = 9;
    err = fwrite(&points, sizeof(int), 1, file);

    // save the coordenates of the points in the file
    double ps[9][3] = {{-100., -100., -100.},
                       {-100., -100., 100.},
                       {100., 100., -100.},
                       {100., 100., 100.},
                       {-100., 100., -100.},
                       {-100., 100., 100.},
                       {100., -100., -100.},
                       {100., -100., 100.},
                       {0., -150., 0.}};

    err = fwrite(ps, sizeof(double), points * 3, file);

    // save the amount of coordinates in the file
    const int conections = 36;
    err = fwrite(&conections, 4, 1, file);

    // save the conections of the points in the file
    int cs[36][2] = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {8, 6}, {8, 7}};
    err = fwrite(cs, sizeof(int), conections * 2, file);

    // Close the file
    err = fclose(file);

    //====================READING THE FILES====================
    /*
    file = fopen(filename, "rb");
    while (file == NULL) file = fopen(filename, "rb");

    Entity *ent = entCreate();
    memset(ent, 0, sizeof(Entity));

    ent->center = vec4Create(0, 0, 0);

    if (fread(&ent->pointsAmount, sizeof(int), 1, file) < 0) perror("error\n");
    printf("Points amount %d\n", ent->pointsAmount);

    ent->p4List = (vec4 *)malloc(ent->pointsAmount * sizeof(vec4));

    while (ent->p4List == NULL) ent->p4List = (vec4 *)malloc(ent->pointsAmount * sizeof(vec4));

    for (int i = 0; i < ent->pointsAmount; i++)
    {
        printf("%d: ", i + 1);

        if (fread(&ent->p4List[i].x, sizeof(double), 1, file) < 0) perror("error\n");
        if (fread(&ent->p4List[i].y, sizeof(double), 1, file) < 0) perror("error\n");
        if (fread(&ent->p4List[i].z, sizeof(double), 1, file) < 0) perror("error\n");
        ent->p4List[i].w = 1;

        printf("x:%f y:%f z:%f w:%f\n", ent->p4List[i].x, ent->p4List[i].y, ent->p4List[i].z, ent->p4List[i].w);
    }

    if (fread(&ent->conections, sizeof(int), 1, file) < 0) perror("error\n");
    printf("Connections amount %d\n", ent->conections);

    ent->conectionsList = (conection *)malloc(ent->conections * sizeof(conection));

    while (ent->conectionsList == NULL) ent->conectionsList = (conection *)malloc(ent->conections * sizeof(conection));

    // initialize the values of the conections
    for (int i = 0; i < ent->conections; i++)
    {
        printf("%d: ", i + 1);
        if (fread(&ent->conectionsList[i], sizeof(conection), 1, file) < 0) perror("error\n");
        printf("%d %d\n", ent->conectionsList[i].x, ent->conectionsList[i].y);
    }

    if (file == NULL) fclose(file);

    entFree(ent);
    */

    return 0;
}