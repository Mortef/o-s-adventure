// character.h
#pragma once

class Character {
public:
    Character(float size, float x, float y);
    float getSize() const;
    float getX() const;    
    float getY() const;
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void draw();

private:
    float size;
    float x;
    float y;
};
