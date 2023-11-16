#include "game.h"
#include "constants.h"
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        return -1;
    }

    // Set GLFW to use double-buffering
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "O's Adventure", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    Game game(window);
    game.initialize();

    while (!glfwWindowShouldClose(window)) {
        game.update();
        game.render();
    }

    glfwTerminate();
    return 0;
}
