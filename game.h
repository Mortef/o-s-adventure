// game.h
#pragma once

#include "character.h"
#include "hexagon.h"
#include <GLFW/glfw3.h>
#include <vector>

class Game {
public:
    Game(GLFWwindow* window); // Add the GLFWwindow as a parameter to the constructor
    void initialize();
    void update();
    void render();
    void reset();
    ~Game();

private:
    Character character;
    std::vector<Hexagon> hexagons;
    GLFWwindow* window; // Store the GLFW window as a class member

    void generateMap();
    void updateMap();
    bool randomBoolean();
    void initOpenAL();
    void cleanupOpenAL();
    bool isGameOver;
    int colCounter;
};
