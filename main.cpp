#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Declare some constant values.
#define WIDTH 800
#define HEIGHT 800
#define WINDOW_NAME "Storm of Lights"

using namespace std;

int main (void) {
    glfwInit();

    // Boilerplate version checking after initialization.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window.
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);
    if (window == NULL) {
        cerr << "Failed to create OpenGL window..." << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Create the main game loop
    bool RUNNING {true};
    while (RUNNING) {
        if (glfwWindowShouldClose(window)) {
            RUNNING = false;
        }

        // Process pooled events
        glfwPollEvents();
    }

    // Call appropriate window destructor functions
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
