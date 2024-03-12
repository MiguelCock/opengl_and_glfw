#include "src/Include.h"

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
    int points = 5;
    err = fwrite(&points, sizeof(int), 1, file);

    // save the coordenates of the points in the file
    double ps[5][2] = {{-100., -100.}, {100., -100.}, {100., 100.}, {-100., 100.}, {0., 0.}};
    err = fwrite(ps, sizeof(double), points * 2, file);

    // save the amount of coordinates in the file
    int conections = 6;
    err = fwrite(&conections, 4, 1, file);

    // save the conections of the points in the file
    int cs[6][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0}};
    err = fwrite(cs, sizeof(int), conections * 2, file);

    // Close the file
    err = fclose(file);

    //====================READING THE FILES====================

    // Open the file
    file = fopen(filename, "rb");

    // Check if file opened successfully
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file '%s'\n", filename);
        return 1;
    }

    // create the entity
    struct Entity *ent = entCreate();

    // read and save the amount of points
    err = fread(&ent->pointsAmount, sizeof(int), 1, file);
    printf("Points amount '%d'\n", ent->pointsAmount);

    // initialize the list of points in the heap
    ent->p3List = (struct Point3 *)calloc(ent->pointsAmount, sizeof(struct Point3));

    // itinialize the values of the points
    for (int i = 0; i < ent->pointsAmount; i++)
    {
        printf("%d: ", i + 1);
        err = fread(&ent->p3List[i].x, sizeof(double), 1, file);
        err = fread(&ent->p3List[i].y, sizeof(double), 1, file);
        ent->p3List[i].w = 1;

        printf("x:%f y:%f\n", ent->p3List[i].x, ent->p3List[i].y);
    }

    // read and save the amount of conections
    err = fread(&ent->conections, sizeof(int), 1, file);
    printf("Points amount '%d'\n", ent->conections);

    // initialize the list of conections in the heap
    ent->conectionsList = (int *)malloc(ent->conections * 2 * sizeof(int));

    // initialize the values of the conections
    for (int i = 0; i < ent->conections; i++)
    {
        printf("%d: ", i + 1);
        err = fread(&ent->conectionsList[i], sizeof(int), 2, file);
        printf("%d %d\n", ent->conectionsList[i], ent->conectionsList[i + 1]);
    }

    // Close the file
    if (file != NULL)
    {
        fclose(file);
    }

    entFree(ent);

    return 0;
}