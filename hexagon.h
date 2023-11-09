// hexagon.h
#pragma once

#include <GLFW/glfw3.h>

class Hexagon {
public:
    Hexagon(float size, bool isBlack, float x, float y);
    void draw();

private:
    float size;
    bool isBlack;
    float x;
    float y;
};
