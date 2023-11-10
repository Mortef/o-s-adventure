// hexagon.h
#pragma once

class Hexagon {
public:
    Hexagon(float size, bool isBlack, float x, float y);
    float getSize() const;
    float getX() const;
    void setX(float x);
    float getY() const;
    bool isBlackHexagon() const;
    void draw();

private:
    float size;
    bool isBlack;
    float x;
    float y;
};
