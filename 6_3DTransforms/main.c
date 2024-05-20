#include "src/Include.h"

/*
const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.f, 0.f, 0.f, 0.f);\n"
    "}\n\0";
*/

int main(void)
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGTH, "2DTranforms", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    Entity *ent = entReadFile("entity.bin");
    mat4 projection = m4CreateProyection(80., 9./16., 0.1, 1000.);
    mat4 up = m4Translation(0, -5, 0);
    mat4 down = m4Translation(0, 5, 0);
    mat4 left = m4Translation(5, 0, 0);
    mat4 right = m4Translation(-5, 0, 0);
    mat4 front = m4Translation(0, 0, 20);
    mat4 back = m4Translation(0, 0, -20);
    mat4 rotatex = m4CreateRX(1);
    mat4 rotatey = m4CreateRY(1);
    mat4 rotatez = m4CreateRZ(1);
    mat4 scaleup = m4Scaling(1.1);
    mat4 scaledown = m4Scaling(0.9);

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

        //translate

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            entTransform(ent, &left);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            entTransform(ent, &down);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
           entTransform(ent, &right);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            entTransform(ent, &up);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            entTrueTrans(ent, &rotatex);
            //entTransform(ent, &rotatex);
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            entTrueTrans(ent, &rotatey);
            //entTransform(ent, &rotatey);
        }
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
            entTrueTrans(ent, &rotatez);
            //entTransform(ent, &rotatez);
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            entTransform(ent, &front);
        }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            entTransform(ent, &back);
        }
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            entTrueTrans(ent, &scaleup);
        }
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            entTrueTrans(ent, &scaledown);
        }
    
        //entTrueTrans(ent, &rotatey);
        
        entDraw(ent, &projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /*
    // Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Shader Program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and buffers
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f,  0.5f,
         0.9f,  0.3f,
         0.5f,  -0.5f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 4);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    */

    glfwDestroyWindow(window);
    glfwTerminate();
    

    entFree(ent);

    exit(EXIT_SUCCESS);
}