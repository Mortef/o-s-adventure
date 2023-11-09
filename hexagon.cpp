// hexagon.cpp
#include "hexagon.h"
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

Hexagon::Hexagon(float size, bool isBlack, float x, float y)
    : size(size), isBlack(isBlack), x(x), y(y) {
    // Constructor
}

void Hexagon::draw() {
    glLineWidth(3.0f); // Adjust the thickness as needed

    // Draw the grey border around the hexagon
    glColor3f(0.5f, 0.5f, 0.5f); // Grey color
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 6; i++) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / 6;
        float xOffset = size * cosf(angle);
        float yOffset = size * sinf(angle);
        glVertex2f(xOffset, yOffset);
    }

    glEnd();

    glPopMatrix();

    // Set color based on hexagon type (inside color)
    if (isBlack) {
        glColor3f(0.0f, 0.0f, 0.0f); // Black color
    }
    else {
        glColor3f(1.0f, 1.0f, 1.0f); // White color
    }

    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glBegin(GL_POLYGON);

    for (int i = 0; i < 6; i++) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / 6;
        float xOffset = size * cosf(angle);
        float yOffset = size * sinf(angle);
        glVertex2f(xOffset, yOffset);
    }

    glEnd();

    glPopMatrix();
}
