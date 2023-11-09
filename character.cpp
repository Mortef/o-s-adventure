// player.cpp
#include <GLFW/glfw3.h>
#include "constants.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;


// character.cpp
#include "character.h"
#include <GLFW/glfw3.h>

Character::Character(float size, float x, float y) : size(size), x(x), y(y) {
    // Constructor
}

void Character::moveUp() {
    if (y < (1.0f - (CHAR_SIZE * 2))) {
        y += CHAR_SPEED;

        // Remove iostream and std lines when removing
        cout << y;
        cout << '\n';
    }
}

void Character::moveDown() {
    if (y >  ((CHAR_SIZE * 2) - 1.0f)) {
        y -= CHAR_SPEED;
        cout << y;
        cout << '\n';
    }
}

void Character::draw() {
    // Draw the character (circle)
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float radian = static_cast<float>(i * (M_PI / 180));
        float xOffset = size * cos(radian); // Adjusted size for the black border
        float yOffset = size * sin(radian); // Adjusted size for the black border
        glVertex2f(xOffset, yOffset);
    }
    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f); // White color
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
