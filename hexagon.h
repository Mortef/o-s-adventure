// hexagon.h
#pragma once

class Hexagon {
public:
    Hexagon(float size, bool isBlack);
    void draw(float x, float y);

private:
    float size;
    bool isBlack;
};
