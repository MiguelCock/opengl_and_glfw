#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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

void freeObject(struct Object *obj)
{
    free(obj->conectionsList);
    free(obj->vertexList);
    free(obj);
}

struct Object *readFile()
{
    FILE *file = fopen("percha.txt", "r");

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(EXIT_FAILURE);
    }

    struct Object *obj = (struct Object *)malloc(sizeof(struct Object));

    char buffer[15];

    if (fgets(buffer, 15, file) != NULL)
    {
        printf("Vertex read: %s", buffer);
        obj->vertex = (int)buffer[0] - 48;
        obj->vertexList = (struct Point *)malloc(obj->vertex * sizeof(struct Point));
    }

    int i = 0;
    while (i < obj->vertex && fgets(buffer, 15, file) != NULL)
    {
        int x = 0;
        int y = 0;

        printf("%d ", i);
        printf("Line read: %s", buffer);

        x += 100 * ((int)buffer[0] - 48);
        x += 10 * ((int)buffer[1] - 48);
        x += ((int)buffer[2] - 48);

        y += 100 * ((int)buffer[4] - 48);
        y += 10 * ((int)buffer[5] - 48);
        y += ((int)buffer[6] - 48);

        printf("%d ", x);
        printf("%d\n", y);

        obj->vertexList[i].x = x;
        obj->vertexList[i].y = y;
        i++;
    }

    if (fgets(buffer, 15, file) != NULL)
    {
        printf("Connections read: %s", buffer);
        obj->conections = (int)buffer[0] - 48;
        obj->conectionsList = (struct Point *)malloc(obj->conections * sizeof(struct Point));
    }

    i = 0;
    while (i != obj->conections && fgets(buffer, 15, file) != NULL)
    {
        int x = 0;
        int y = 0;

        printf("Line read: %s", buffer);

        x = ((int)buffer[0] - 48);
        y = ((int)buffer[2] - 48);

        printf("%d ", x);
        printf("%d\n", y);

        obj->conectionsList[i].x = x;
        obj->conectionsList[i].y = y;
        i++;
    }

    fclose(file);

    return obj;
}

void drawObject(struct Object *obj)
{
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < obj->conections; ++i)
    {
        int p1 = obj->conectionsList[i].x;
        int p2 = obj->conectionsList[i].y;

        glVertex2i(obj->vertexList[p1].x, obj->vertexList[p1].y);
        glVertex2i(obj->vertexList[p2].x, obj->vertexList[p2].y);
    }

    glEnd();
}

int main(void)
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(640, 480, "Casa", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    struct Object *obj = readFile();

    glClearColor(0.7f, 0.7f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        drawObject(obj);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    freeObject(obj);

    glfwTerminate();

    exit(EXIT_SUCCESS);
}