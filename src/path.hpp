#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

#include "enemy.hpp"


#define PI 3.14159265358979323846
class Enemy;

struct Path {
    std::vector<sf::Vector2f> path;

    void move_in_path(Enemy& obj);
};