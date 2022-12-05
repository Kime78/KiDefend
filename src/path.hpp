#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include "enemy.hpp"

struct Path {
    std::vector<sf::Vector2f> path;

    void move_in_path(Enemy& obj);
};