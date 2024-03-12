#include "src/Include.h"

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

    struct Entity *ent = entReadFile();

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

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

        //drawings

        entDraw(ent);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    entFree(ent);

    exit(EXIT_SUCCESS);
}