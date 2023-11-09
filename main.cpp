#include <GLFW/glfw3.h>
#include "game.h"
#include "constants.h"
#include <iostream>
using namespace std;

int main() {
    if (!glfwInit()) {
        return -1;
    }

    // Set GLFW to use double-buffering
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hexagon Game", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    Game game(window); // Pass the GLFW window to the Game constructor
    game.initialize();

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    int width2, height2;
    glfwGetFramebufferSize(window, &width2, &height2);

    int left, top, right, bottom;
    glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);

    cout << left;
    cout << '\n';
    cout << top;
    cout << '\n';
    cout << right;
    cout << '\n';
    cout << bottom;

    while (!glfwWindowShouldClose(window)) {
        // Remove iostream and std lines when removing
        GLenum error = glGetError(); // Check for OpenGL errors at the start
        if (error != GL_NO_ERROR) {
            cout << error;
        }

        game.update();
        game.render();

        error = glGetError(); // Check for OpenGL errors at the end
        if (error != GL_NO_ERROR) {
            cout << error;
        }
    }

    glfwTerminate();
    return 0;
}
