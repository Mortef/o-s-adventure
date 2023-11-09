// character.h
#pragma once

class Character {
public:
    Character(float size, float x, float y);
    void moveUp();
    void moveDown();
    void draw();

private:
    float size;
    float x;
    float y;
};
