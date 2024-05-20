#include "Entity3D.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>

Entity *entCreate()
{
    Entity *ent = (Entity *)malloc(sizeof(Entity));

    while (ent == NULL) ent = (Entity *)malloc(sizeof(Entity));

    ent->center.x = 0;
    ent->center.y = 0;
    ent->center.w = 0;
    //ent->angle = 0;

    return ent;
}

void entFree(Entity *ent)
{
    free(ent->p4List);
    free(ent->conectionsList);
    free(ent);
}

void entDraw(Entity *ent, mat4 *proyection)
{
    glBegin(GL_LINES);

    for (int i = 0; i < ent->conections; i++)
    {
        if (i%2 == 0)
        {
            glColor3f(0.0f, 0.0f, 0.0f);
        } 
        else 
        {
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        
        int p1 = ent->conectionsList[i].x;
        int p2 = ent->conectionsList[i].y;

        //vec4 p11 = vec4Dot(&ent->p4List[p1], proyection);
        //vec4 p22 = vec4Dot(&ent->p4List[p2], proyection);a

        //glVertex2i(vec4Sum(&p11,&ent->center).x, vec4Sum(&p11,&ent->center).y);
        //glVertex2i(vec4Sum(&p22,&ent->center).x, vec4Sum(&p22,&ent->center).y);

        vec4 v41 = vec4Sum(&ent->p4List[p1],&ent->center);
        glVertex2i(v41.x * (SCREEN_WIDTH/v41.z) + SCREEN_WIDTH/2, v41.y * (SCREEN_HEIGTH/v41.z) + SCREEN_HEIGTH/2);
        vec4 v42 = vec4Sum(&ent->p4List[p2],&ent->center);
        glVertex2i(v42.x * (SCREEN_WIDTH/v42.z) + SCREEN_WIDTH/2, v42.y * (SCREEN_HEIGTH/v42.z) + SCREEN_HEIGTH/2);
    }

    glEnd();
}

Entity *entReadFile(char *filename)
{
    FILE *file;

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

    return ent;
}

void entTransform(Entity *ent, mat4 *m4)
{
    ent->center = vec4Dot(&ent->center, m4);
}

void entTrueTrans(Entity *ent, mat4 *m4)
{
    for (int i = 0; i < ent->pointsAmount; i++)
    {
        ent->p4List[i] = vec4Dot(&ent->p4List[i], m4);
    }
}