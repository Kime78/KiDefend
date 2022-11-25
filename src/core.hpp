#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <utility>
#include <array>

#include "level.hpp"

struct Game {
    sf::Texture sprite_matrix;
    sf::RenderWindow* window;
    int health = 50;
    int money = 1000;
    int current_level = 1;
    int current_wave = 1;
    std::array<Level, 5> levels;
    sf::Clock wave_timer;
    sf::Clock enemy_timer;
    void load_sprite(sf::Sprite& obj, std::pair<int, int> index);
    void run();
    void spawn_wave();
    Game(int width, int height, std::string name);
    
};