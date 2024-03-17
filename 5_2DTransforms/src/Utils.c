#include <GLFW/glfw3.h>
#include "Utils.h"

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

#include <stdlib.h>
#include <stdio.h>

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