#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct Point
{
    int x;
    int y;
};

struct linkedList
{
    struct Point p;
    struct linkedList *next;
};

void listAppend(int x, int y, struct linkedList *head)
{
    struct linkedList *h = head;
    for (; h->next != NULL;)
    {
        h = h->next;
    }
    struct linkedList *nxt = (struct linkedList *)malloc(sizeof(struct linkedList));
    nxt->p.x = x;
    nxt->p.y = y;
    h->next = nxt;
}

struct Object
{
    int vertices;
    struct linkedList *pointsList;
    int conections;
    struct linkedList *conectionsList;
};

struct Object *readFile()
{
    FILE *file = fopen("casa.txt", "r");

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(EXIT_FAILURE);
    }

    struct Object *obj = (struct Object *)malloc(sizeof(struct Object));

    char buffer[15];

    if (fgets(buffer, 15, file) != NULL)
    {
        printf("Line read: %s", buffer);
        obj->vertices = (int)buffer[0] - 48;
    }

    int i = 0;
    while (fgets(buffer, 15, file) != NULL && i != obj->vertices)
    {
        struct linkedList *h = obj->pointsList;

        int x = 0;
        int y = 0;

        printf("Line read: %s", buffer);

        x += 100 * ((int)buffer[0] - 48);
        x += 10 * ((int)buffer[1] - 48);
        x += ((int)buffer[2] - 48);
        y += 100 * ((int)buffer[4] - 48);
        y += 10 * ((int)buffer[5] - 48);
        y += ((int)buffer[6] - 48);

        printf("%d ", x);
        printf("%d\n", y);
        
        struct linkedList *nxt = (struct linkedList *)malloc(sizeof(struct linkedList));
        nxt->p.x = x;
        nxt->p.y = y;
        h->next = nxt;
        h = h->next;

        i++;
    }

    fclose(file);

    return obj;
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
    printf("%d\n", obj->vertices);

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

        glBegin(GL_LINE_LOOP);

        glColor3f(0.0f, 1.0f, 0.0f);

        glVertex2i(100, 100);
        glVertex2i(200, 100);
        glVertex2i(200, 200);
        glVertex2i(150, 250);
        glVertex2i(100, 200);

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    exit(EXIT_SUCCESS);
}