// game.h
#pragma once

#include <vector>
#include "character.h"
#include "hexagon.h"

class Game {
public:
    Game(GLFWwindow* window); // Add the GLFWwindow as a parameter to the constructor
    void initialize();
    void update();
    void render();

private:
    Character character;
    std::vector<Hexagon> hexagons;
    GLFWwindow* window; // Store the GLFW window as a class member

    void generateMap();
    bool randomBoolean();
};
