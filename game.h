// game.h
#pragma once

#include <vector>
#include "player.h"
#include "hexagon.h"

class Game {
public:
    Game();
    void initialize();
    void update();
    void render();

private:
    Player player;
    std::vector<Hexagon> hexagons;
};
