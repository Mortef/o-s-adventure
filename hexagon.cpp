// hexagon.cpp
#define _USE_MATH_DEFINES
#include "hexagon.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

Hexagon::Hexagon(float size, bool isBlack, float x, float y) : size(size), isBlack(isBlack), x(x), y(y) {}

float Hexagon::getSize() const { return size; }
float Hexagon::getX() const { return x; }
float Hexagon::getY() const { return y; }
void Hexagon::setX(float x) { this->x = x; }

bool Hexagon::isBlackHexagon() const { return isBlack; }

void Hexagon::draw() {
    glLineWidth(4.0f); // Adjust the thickness

    // Draw the border around the hexagon
    glColor3f(0.5f, 0.5f, 0.5f);
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

    // Set inside color based on hexagon type
    isBlack ? glColor3f(0.0f, 0.0f, 0.0f) : glColor3f(1.0f, 1.0f, 1.0f);
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
