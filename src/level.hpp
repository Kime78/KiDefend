#pragma once
#include "path.hpp"
#include "enemy.hpp"
struct Level
{
    Path path;
    int level_num;
    sf::Sprite level_sprite; //or maybe a matrix of sprites to make it tile BASED
    std::queue<Wave> waves;

    void load_level();
};
