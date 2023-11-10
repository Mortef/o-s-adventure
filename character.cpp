// character.cpp
#define _USE_MATH_DEFINES
#include "constants.h"
#include "character.h"
#include <GLFW/glfw3.h>
#include <cmath>

Character::Character(float size, float x, float y) : size(size), x(x), y(y) {}

float Character::getSize() const {
    return size;
}

float Character::getX() const {
    return x;
}
float Character::getY() const {
    return y;
}

void Character::moveUp() {
    // Check border of the map
    if (y < (1.0f - CHAR_SIZE)) {
        y += CHAR_SPEED;
    }
}

void Character::moveDown() {
    if (y >  (CHAR_SIZE - 1.0f)) {
        y -= CHAR_SPEED;
    }
}

void Character::moveRight() {
    if (x < (1.0f - CHAR_SIZE) && ALL_DIRECTIONS) {
        x += CHAR_SPEED;
    }
}

void Character::moveLeft() {
    if (x > (CHAR_SIZE - 1.0f) && ALL_DIRECTIONS) {
        x -= CHAR_SPEED;
    }
}

void Character::draw() {
    // Draw the character (circle)
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.0f, 0.0f, 0.0f); // Black color

    // A bigger black circle is drawn to work as a border
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float radian = static_cast<float>(i * (M_PI / 180));
        float xOffset = size * cos(radian);
        float yOffset = size * sin(radian);
        glVertex2f(xOffset, yOffset);
    }
    glEnd();

    // On top of the black circle, another smaller grey circle is drawn
    glColor3f(0.9f, 1.0f, 1.0f); // Light grey color
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float radian = static_cast<float>(i * (M_PI / 180));
        float xOffset = size * 0.9f * cos(radian);
        float yOffset = size * 0.9f * sin(radian);
        glVertex2f(xOffset, yOffset);
    }
    glEnd();
    glPopMatrix();
}
