#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void bresenhamLine(int x1, int y1, int x2, int y2) {
    /*
    int dx, dy, p, x, y;  
    dx=x1-x0;  
    dy=y1-y0;  
    x=x0;  
    y=y0;  
    p=2*dy-dx;  
    while(x<x1) {  
        if(p>=0) {  
            glVertex2i(x, y);  
            y=y+1;  
            p=p+2*dy-2*dx;  
        }  
        else {  
            glVertex2i(x, y); 
            p=p+2*dy;
            x=x+1;  
        }  
    }
    */
    int dx = x2 - x1;
    if (dx < 0) dx*=-1;
    int dy = y2 - y1;
    if (dy < 0) dy*=-1;
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        glVertex2i(x1, y1); 
        if (x1 == x2 && y1 == y2) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_W) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        static double xpos1, ypos1;
        static double xpos2, ypos2;

        if (xpos1 == 0.0 && ypos1 == 0.0) {
            glfwGetCursorPos(window, &xpos1, &ypos1);
            printf("FIRST Mouse clicked at position (%.0f, %.0f)\n", xpos1, ypos1);
        } else {
            glfwGetCursorPos(window, &xpos2, &ypos2);
            printf("SECOND Mouse clicked at position (%.0f, %.0f)\n", xpos2, ypos2);

            
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, width, height, 0, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            // Draw a red pixel at coordinates (100, 100)
            glBegin(GL_POINTS);

            glColor3f(1.0f, 0.0f, 0.0f);
            bresenhamLine((int)xpos1, (int)ypos1, (int)xpos2, (int)ypos2);

            glEnd();

            glfwSwapBuffers(window);
            
            xpos1 = 0;
            ypos1 = 0;
        }
    }
}

/*
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    printf("Cursor position: (%.2f, %.2f)\n", xpos, ypos);
}
*/

int main(void) {
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    //glfwSetCursorPosCallback(window, cursor_position_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glClearColor(0.7f, 0.7f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        /*
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Draw a red pixel at coordinates (100, 100)
        glBegin(GL_POINTS);

        glColor3f(1.0f, 0.0f, 0.0f);
        for(int i = 0; i<200; i++) {
            glVertex2i(i, i);
        }

        glEnd();

        glfwSwapBuffers(window);
        */
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
