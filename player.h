// player.h
#pragma once

class Player {
public:
    Player(float size, float x, float y);
    void draw();
    void moveUp();
    void moveDown();

private:
    float size;
    float x;
    float y;
};
