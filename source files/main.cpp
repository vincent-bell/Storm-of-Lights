#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Declare some constant values.
#define WIDTH 700
#define HEIGHT 700
#define WINDOW_NAME "Storm of Lights"

using namespace std;

// Define shader source code here
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main (void) {\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main (void) {\n"
"    FragColor = vec4(0.3f, 0.7f, 0.22f, 1.0f);\n"
"}\n\0";

int main (void) {
    // Initialize GLFW
    glfwInit();


    // Boilerplate version checking after initialization. (OpenGL 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Inform GLFW we want to use the CORE profile which contains only the modern functions.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Define the vertices for drawing an equilateral triangle.
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };


    // Create the window with error checking.
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);
    if (window == NULL) {
        cerr << "Failed to create OpenGL window..." << endl;
        glfwTerminate();
        return -1;
    }


    // Load the window we just created into the current context.
    glfwMakeContextCurrent(window);

    // Load glad
    gladLoadGL();

    // Specify the viewport of OpenGL (x = 0, y = 0 to x=WIDTH, y=HEIGHT)
    glViewport(0, 0, WIDTH, HEIGHT);


    // Initialize shader objects
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Wrap shaders into a single shader program and then link it.
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Once shaders are in program we can delete the objects.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // I have no idea...
    // Something about creating a buffer for CPU-GPU comms to reduce number of times we request due to slow send/recieve?
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Colour is represented by normalized floats R, G, B where ALPHA represents the transparency.
    // ALPHA: 1.0 - opaque, 0.0 - completely transparent
    glClearColor(0.77f, 0.79f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the front and back buffers to paint the colours from the back buffer onto the visable front one.
    glfwSwapBuffers(window);

    // Create the main game loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.77f, 0.79f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        // Process pooled events
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Call appropriate window destructor functions
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
