#include "src/Include.h"

int main(void)
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(640, 480, "2DTranforms", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    struct Entity *ent = entReadFile();
    struct Matrix3x3* moveX = m3Trasnlate(5, 0);
    struct Matrix3x3* moveY = m3Trasnlate(0, 5);
    struct Matrix3x3* moveXm = m3Trasnlate(-5, 0);
    struct Matrix3x3* moveYm = m3Trasnlate(0, -5);
    struct Matrix3x3* scaleM = m3Scale(1.1);
    struct Matrix3x3* rotateM = m3Rotate(1);

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

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            entTransform(ent, moveX);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            entTransform(ent, moveY);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            entTransform(ent, moveXm);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            entTransform(ent, moveYm);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            entTransform(ent, scaleM);
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            entTransform(ent, rotateM);
        }
        
        entDraw(ent);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    entFree(ent);
    m3Free(moveX);
    m3Free(moveY);
    m3Free(moveXm);
    m3Free(moveYm);

    exit(EXIT_SUCCESS);
}