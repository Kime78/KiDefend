#pragma once
#include <map>
#include <SFML/Graphics.hpp>

class Game {
    std::map<sf::Image> images;
    void render();
};