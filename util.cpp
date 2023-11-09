// util.cpp
#include "util.h"
#include <GLFW/glfw3.h>
#include "constants.h"
#include <iostream>
#include <string>

double calculateFPS() {
    static double previousTime = 0.0;
    static int frameCount = 0;
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - previousTime;
    double fps = 1.0 / deltaTime;
    frameCount++;

    if (deltaTime >= 1.0) {
        fps = static_cast<double>(frameCount) / deltaTime;
        frameCount = 0;
        previousTime = currentTime;
    }

    return fps;
}

void drawFPS() {
    double fps = calculateFPS();
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glRasterPos2f(10, SCREEN_HEIGHT - 30); // Position for the FPS text
    const char* fpsText = ("FPS: " + std::to_string(fps)).c_str();
    int length = static_cast<int>(strlen(fpsText));
    for (int i = 0; i < length; i++) {
        char c = fpsText[i];
        //glRasterPos2i(xpos, ypos);
    }
}