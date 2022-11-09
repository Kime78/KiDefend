#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include "enemy.hpp"

struct Path {
    std::queue<sf::Vector2f> path;

    void move_in_path(Enemy& obj, float speed);
};