#include "Entity.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

struct Entity *entCreate()
{
    struct Entity *ent = (struct Entity *)malloc(sizeof(struct Entity *));
    ent->center.x = 0;
    ent->center.y = 0;
    ent->center.w = 0;
    ent->angle = 0;

    return ent;
}

void entFree(struct Entity *ent)
{
    free(ent->p3List);
    free(ent->conectionsList);
    free(ent);
}

void entDraw(struct Entity *ent)
{
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < ent->conections; i++)
    {
        int p1 = ent->conectionsList[i];
        int p2 = ent->conectionsList[i+1];

        glVertex2i(ent->p3List[p1].x, ent->p3List[p1].y);
        glVertex2i(ent->p3List[p2].x, ent->p3List[p2].y);
    }

    glEnd();
}

struct Entity *entReadFile()
{
    int err;
    FILE *file;
    char filename[] = "entity.bin";

    // Open the file
    file = fopen(filename, "rb");

    // Check if file opened successfully
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file '%s'\n", filename);
        return NULL;
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
    if (file == NULL)
    {
        fclose(file);
    }

    /*if (err == 0)
    {
        return NULL;
    }*/

    return ent;
}

void entTransform(struct Entity *ent, struct Matrix3x3 *m3)
{
    p3Dot(&ent->center,m3);

    for (int i = 0; i < ent->pointsAmount; i++)
    {
        p3Dot(&ent->p3List[i], m3);
    }
}