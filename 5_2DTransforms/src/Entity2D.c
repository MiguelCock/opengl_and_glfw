#include "Entity2D.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>

Entity *entCreate()
{
    Entity *ent = (Entity *)malloc(sizeof(Entity));

    while (ent == NULL)
        ent = (Entity *)malloc(sizeof(Entity));

    ent->center.x = 0;
    ent->center.y = 0;
    ent->center.w = 0;
    ent->angle = 0;

    return ent;
}

void entFree(Entity *ent)
{
    free(ent->p3List);
    free(ent->conectionsList);
    free(ent);
}

void entDraw(Entity *ent)
{
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < ent->conections; i++)
    {
        int p1 = ent->conectionsList[i].x;
        int p2 = ent->conectionsList[i].y;

        glVertex2i(ent->p3List[p1].x, ent->p3List[p1].y);
        glVertex2i(ent->p3List[p2].x, ent->p3List[p2].y);
    }

    glEnd();
}

Entity *entReadFile(char *filename)
{
    FILE *file;

    file = fopen(filename, "rb");
    while (file == NULL)
        file = fopen(filename, "rb");

    Entity *ent = entCreate();
    memset(ent, 0, sizeof(Entity));

    ent->center = (Point3){x : 0, y : 0, w : 1};

    if (fread(&ent->pointsAmount, sizeof(int), 1, file) < 0)
        perror("error\n");
    printf("Points amount %d\n", ent->pointsAmount);

    ent->p3List = (Point3 *)malloc(ent->pointsAmount * sizeof(Point3));

    while (ent->p3List == NULL)
        ent->p3List = (Point3 *)malloc(ent->pointsAmount * sizeof(Point3));

    for (int i = 0; i < ent->pointsAmount; i++)
    {
        printf("%d: ", i + 1);

        if (fread(&ent->p3List[i].x, sizeof(double), 1, file) < 0)
            perror("error\n");
        if (fread(&ent->p3List[i].y, sizeof(double), 1, file) < 0)
            perror("error\n");
        ent->p3List[i].w = 1;

        printf("x:%f y:%f w:%f\n", ent->p3List[i].x, ent->p3List[i].y, ent->p3List[i].w);
    }

    if (fread(&ent->conections, sizeof(int), 1, file) < 0)
        perror("error\n");
    printf("Connections amount %d\n", ent->conections);

    ent->conectionsList = (conection *)malloc(ent->conections * sizeof(conection));

    while (ent->conectionsList == NULL)
        ent->conectionsList = (conection *)malloc(ent->conections * sizeof(conection));

    // initialize the values of the conections
    for (int i = 0; i < ent->conections; i++)
    {
        printf("%d: ", i + 1);
        if (fread(&ent->conectionsList[i], sizeof(conection), 1, file) < 0)
            perror("error\n");
        printf("%d %d\n", ent->conectionsList[i].x, ent->conectionsList[i].y);
    }

    if (file == NULL)
        fclose(file);

    return ent;
}

void entTransform(Entity *ent, Matrix3x3 *m3)
{
    for (int i = 0; i < ent->pointsAmount; i++)
    {
        p3Dot(&ent->p3List[i], m3);
    }
}