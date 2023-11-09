// game.cpp
#include "game.h"
#include "constants.h"
#include <random>

Game::Game(GLFWwindow* window) : window(window), character(20.0f, 100.0f, SCREEN_HEIGHT / 2.0f) {
    // Constructor
}

void Game::initialize() {
    // Initialize player
    character = Character(CHAR_SIZE, 1.0f - (CHAR_SIZE * 2), 0.0f);

    // Initialize hexagons (generate the map here)
    generateMap();
}

void Game::update() {
    // Update player movement based on input
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        character.moveUp();
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        character.moveDown();
    }

    // Check for collisions with hexagons

    // End the game if the player is on a black hexagon
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the map of hexagons
    for (Hexagon& hexagon : hexagons) {
        hexagon.draw();
    }

    // Draw the player
    character.draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Game::generateMap() {
    // Calculate the number of hexagons that can fit in the screen width
    int numHexagonsX = static_cast<int>(1.0f / HEX_SIZE * 2 + 2);

    // Calculate the number of hexagons that can fit in the screen height
    int numHexagonsY = static_cast<int>(1.0f / HEX_SIZE + 4);

    // Create the map of hexagons
    for (int col = 1; col < numHexagonsX + 1; col++) {

        for (int row = 1; row < numHexagonsY + 1; row++) {
            float xPos = col * HEX_SIZE * 1.5f - 1.08f;
            float yPos = row * HEX_SIZE * 1.8f - 1.08f;
            if (col % 2 == 0) { yPos = yPos - (HEX_SIZE * 0.9f); }

            //bool isBlack = (col < numHexagonsX - 11) ? randomBoolean() : false;
            bool isBlack = randomBoolean();

            hexagons.push_back(Hexagon(HEX_SIZE, isBlack, xPos, yPos));
        }
    }
}

bool Game::randomBoolean() {
    static std::default_random_engine generator(std::random_device{}());
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    float generatedNum = distribution(generator);
    return (generatedNum > 0.75f) ? true : false;
}