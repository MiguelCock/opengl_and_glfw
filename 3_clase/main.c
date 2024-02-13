#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "src/Vector3.h"

//Cohen Sutherland boundaries
#define INSIDE 0 // 0000
#define LEFT 1   // 0001
#define RIGHT 2  // 0010
#define BOTTOM 4 // 0100
#define TOP 8    // 1000

const double XMIN = 160;
const double XMAX = 480;
const double YMIN = 120;
const double YMAX = 360;

int ComputeOutCode(double x, double y)
{
	int code = INSIDE;

	if (x < XMIN) code |= LEFT;         // to the left of clip window
	else if (x > XMAX) code |= RIGHT;   // to the right of clip window
	if (y < YMIN) code |= BOTTOM;       // below the clip window
	else if (y > YMAX) code |= TOP;     // above the clip window

	return code;
}

bool CohenSutherlandLineClip(double* x0, double* y0, double* x1, double* y1){
	int outcode0 = ComputeOutCode(*x0, *y0);
	int outcode1 = ComputeOutCode(*x1, *y1);
	bool accept = false;

	while (true) {
		if (!(outcode0 | outcode1)) {
			accept = true;
			break;
		} else if (outcode0 & outcode1) {
			break;
		} else {

			double x, y;

			int outcodeOut = outcode1 > outcode0 ? outcode1 : outcode0;

			if (outcodeOut & TOP) {
				x = *x0 + (*x1 - *x0) * (YMAX - *y0) / (*y1 - *y0);
				y = YMAX;
			} else if (outcodeOut & BOTTOM) {
				x = *x0 + (*x1 - *x0) * (YMIN - *y0) / (*y1 - *y0);
				y = YMIN;
			} else if (outcodeOut & RIGHT) { 
				y = *y0 + (*y1 - *y0) * (XMAX - *x0) / (*x1 - *x0);
				x = XMAX;
			} else if (outcodeOut & LEFT) {
				y = *y0 + (*y1 - *y0) * (XMIN - *x0) / (*x1 - *x0);
				x = XMIN;
			}

			if (outcodeOut == outcode0) {
				*x0 = x;
				*y0 = y;
				outcode0 = ComputeOutCode(*x0, *y0);
			} else {
				*x1 = x;
				*y1 = y;
				outcode1 = ComputeOutCode(*x1, *y1);
			}
		}
	}
	return accept;
}

void drawLine(GLFWwindow* window, double x1, double y1, double x2, double y2) {
    //previus lines of the points if they are cut
    int lx1 = (int)x1, lx2 = (int)x2, ly1 = (int)y1, ly2 = (int)y2;
    bool cut = CohenSutherlandLineClip(&x1, &y1, &x2, &y2);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    
    if (cut) {
        //draw green lines
        glBegin(GL_LINES);

        glColor3f(0.0f, 1.0f, 0.0f);

        glVertex2i((int)x1,(int)y1);
        glVertex2i((int)x2,(int)y2);

        glEnd();
    
        //draw red lines
        glBegin(GL_LINES);

        glColor3f(1.0f, 0.0f, 0.0f);

        glVertex2i((int)lx1,(int)ly1);
        glVertex2i((int)x1,(int)y1);

        glVertex2i((int)lx2,(int)ly2);
        glVertex2i((int)x2,(int)y2);

        glEnd();
    } else {
        //draw only red lines
        glBegin(GL_LINES);

        glColor3f(1.0f, 0.0f, 0.0f);

        glVertex2i((int)lx1,(int)ly1);
        glVertex2i((int)lx2,(int)ly2);

        glEnd();
    }

    //draw the border
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2i((int)XMAX,(int)YMAX);
    glVertex2i((int)XMAX,(int)YMIN);
    glVertex2i((int)XMIN,(int)YMIN);
    glVertex2i((int)XMIN,(int)YMAX);

    glEnd();

    glfwSwapBuffers(window);
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glClearColor(0.7f, 0.7f, 1.0f, 1.0f);

    int buttonState = GLFW_RELEASE;
    int prevButtonState = GLFW_RELEASE;
    bool startClick = false;
    double x1, y1, x2, y2;

    while (!glfwWindowShouldClose(window)) {

        buttonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

        if (buttonState == GLFW_PRESS) {
            prevButtonState = GLFW_RELEASE;
        } else {
            prevButtonState = GLFW_PRESS;
        }

        if (buttonState == GLFW_PRESS && startClick) {
            glfwGetCursorPos(window, &x2, &y2);
            drawLine(window, x1, y1, x2, y2);
        } else if (buttonState == GLFW_PRESS && prevButtonState == GLFW_RELEASE) { 
            glfwGetCursorPos(window, &x1, &y1);
            startClick = true;
        } else if (buttonState == GLFW_RELEASE && prevButtonState == GLFW_PRESS) {
            startClick = false;
        }
        
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    struct vec3 a = {1, 1, 3};
    printf("%f", a.x);

    exit(EXIT_SUCCESS);
}
