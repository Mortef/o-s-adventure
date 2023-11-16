// game.cpp
#include "game.h"
#include "constants.h"
#include <random>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <iostream>

Game::Game(GLFWwindow* window) : window(window), isGameOver(false), colCounter(1), character(CHAR_SIZE, 1.0f - (CHAR_SIZE * 2), 0.0f) {}

// Add a member variable for the OpenAL source
ALuint backgroundMusicSource;

void Game::initialize() {
    generateMap();
    initOpenAL();
}

Game::~Game() {
    cleanupOpenAL();
}

void Game::update() {
    if (!isGameOver) {
        // Update character movement based on input
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { character.moveUp(); }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { character.moveDown(); }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { character.moveRight(); }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { character.moveLeft(); }

        // Update the map's movement
        updateMap();

        // Check for collisions with hexagons
        for (const Hexagon& hexagon : hexagons) {
            // Calculate the distance between the character and the center of the hexagon
            float distance = sqrt(pow(character.getX() - hexagon.getX(), 2) + pow(character.getY() - hexagon.getY(), 2));

            // If the distance is less than the sum of character and hexagon radii, they overlap
            // But a certain percentage of the character's body is allowed inside the holes
            float charSizeInside = (hexagon.getSize() * 2 * CHAR_MAX_PERCENTAGE_IN_HOLE);
            if (distance < character.getSize() + hexagon.getSize() - charSizeInside) {
                // Check if it's a black hexagon
                if (hexagon.isBlackHexagon()) {
                    alSourceStop(backgroundMusicSource);
                    isGameOver = true;
                }
            }
        }
    }
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (!isGameOver) {

        // Draw the map of hexagons
        for (Hexagon& hexagon : hexagons) {
            hexagon.draw();
        }

        // Draw the character
        character.draw();

        glfwPollEvents();
    }
    else {
        hexagons.clear();

        glClearColor(0.5f, 0.0f, 0.0f, 1.0f); // Set the clear color to red
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        // Check for a space press to reset the game
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            reset();
        }
    }
    glfwSwapBuffers(window);
}

void Game::reset() {
    // Reset the game state
    isGameOver = false;

    colCounter = 1;

    alSourcePlay(backgroundMusicSource);

    glClear(GL_COLOR_BUFFER_BIT);

    // Reset character and any other game elements as needed
    character = Character(CHAR_SIZE, 1.0f - (CHAR_SIZE * 2), 0.0f);

    // Regenerate the map or reinitialize any other game elements
    generateMap();
}

void Game::generateMap() {
    // Calculate the number of hexagons that can fit in the screen width
    int numHexagonsX = static_cast<int>(1.0f / HEX_SIZE + 8.5f);

    // Calculate the number of hexagons that can fit in the screen height
    int numHexagonsY = static_cast<int>(1.0f / HEX_SIZE + 2.5f);

    // Create the map of hexagons
    for (int col = 1; col < numHexagonsX + 1; col++) {
        float xPos = numHexagonsX - col * HEX_SIZE * 1.5f - 19.48f;
        for (int row = 1; row < numHexagonsY + 1; row++) {
            float yPos = row * HEX_SIZE * 1.8f - 1.08f;
            if (col % 2 == 0) { yPos = yPos - (HEX_SIZE * 0.9f); }
            hexagons.insert(hexagons.begin(), Hexagon(HEX_SIZE, false, xPos, yPos));
        }
    }
}

void Game::updateMap() {
    // Move the entire map to the left (decrement the x-coordinate of each hexagon)
    for (Hexagon& hexagon : hexagons) {hexagon.setX(hexagon.getX() + MAP_SPEED);}

    // Check if the rightmost column is out of the screen and remove it
    if (!hexagons.empty() && hexagons.back().getX() > 1.06f) { hexagons.pop_back(); }

    // Check if a new column should be added on the left
    if (hexagons.front().getX() > (HEX_SIZE * 2 - 1.12f)) {
        colCounter++;
        // Calculate the number of hexagons that can fit in the screen height
        int numHexagonsY = static_cast<int>(1.0f / HEX_SIZE + 2.5f);
        float xPos = 1 * HEX_SIZE * 1.5f - 1.20f;

        for (int row = 1; row < numHexagonsY + 1; row++) {
            float yPos = row * HEX_SIZE * 1.8f - 1.08f;
            if (colCounter % 2 == 0) { yPos = yPos - (HEX_SIZE * 0.9f); }
            bool isBlack = randomBoolean();
            hexagons.insert(hexagons.begin(), Hexagon(HEX_SIZE, isBlack, xPos, yPos));
        }
    }
}


bool Game::randomBoolean() {
    static std::default_random_engine generator(std::random_device{}());
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    float generatedNum = distribution(generator);
    return (generatedNum > 0.75f) ? true : false;
}


// Function to initialize OpenAL and load background music
void Game::initOpenAL() {
    ALCdevice* device = alcOpenDevice(NULL);
    if (!device) {
        std::cerr << "Failed to initialize OpenAL device\n";
        return;
    }

    ALCcontext* context = alcCreateContext(device, NULL);
    if (!context) {
        std::cerr << "Failed to create OpenAL context\n";
        alcCloseDevice(device);
        return;
    }

    alcMakeContextCurrent(context);

    // Generate a source
    alGenSources(1, &backgroundMusicSource);

    // Load your MP3 file and set it as the background music
    ALuint buffer = alutCreateBufferFromFile("maze.ogg");
    alSourcei(backgroundMusicSource, AL_BUFFER, buffer);

    // Set the source to loop
    alSourcei(backgroundMusicSource, AL_LOOPING, AL_TRUE);

    // Play the background music
    alSourcePlay(backgroundMusicSource);
}

// Function to clean up OpenAL resources
void Game::cleanupOpenAL() {
    alDeleteSources(1, &backgroundMusicSource);
    ALCcontext* context = alcGetCurrentContext();
    ALCdevice* device = alcGetContextsDevice(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}