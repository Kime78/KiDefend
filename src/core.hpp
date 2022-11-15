#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <utility>

struct Game {
    sf::Texture sprite_matrix;
    int health = 50;
    int money = 1000;
    void load_sprite(sf::Sprite& obj, std::pair<int, int> index);
    void render();
};