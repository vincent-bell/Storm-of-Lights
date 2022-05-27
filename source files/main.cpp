#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Declare some constant values.
#define WIDTH 1000
#define HEIGHT 700
#define WINDOW_NAME "Storm of Lights"

using namespace std;

int main (void) {
    glfwInit();

    // Boilerplate version checking after initialization.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Inform GLFW we want to use the CORE profile which contains only the modern functions.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    // Colour is represented by normalized floats RED, GREEN, BLUE where ALPHA represents the transparency.
    // ALPHA: 1.0 {opaque}, 0.0 {completely transparent}
    glClearColor(0.14f, 0.23f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the front and back buffers to paint the colours from the back buffer onto the visable front one.
    glfwSwapBuffers(window);

    // Create the main game loop
    while (!glfwWindowShouldClose(window)) {

        // Process pooled events
        glfwPollEvents();
    }

    // Call appropriate window destructor functions
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}   
