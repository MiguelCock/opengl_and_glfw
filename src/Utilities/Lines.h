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