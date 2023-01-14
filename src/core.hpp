#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <utility>
#include <array>

#include "enemy.hpp"
#include "level.hpp"
#include "turret.hpp"
#include "bullet.hpp"
#include "button.hpp"
class ShopButton;
struct Game {
    GameObjectContainer objects;
    GameObjectContainer ui;
    std::array<sf::Texture, 10> turret_tex;
    std::array<sf::Texture, 10> enemies_tex;
    std::array<sf::Texture, 10> maps_tex;
    std::array<sf::Texture, 10> bullet_tex;
    std::array<sf::Texture, 10> buttons_tex;
    sf::Sprite map_sprite;
    sf::Texture shop_tex;
    sf::Sprite shop_sprite;
    sf::Text hp_text;
    sf::Text money_text;
    sf::Text wave_text;
    sf::Text win_text;
    sf::Text lose_text;
    sf::Font font;
    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies;
    std::vector<Turret*> turrets;
    sf::RenderWindow* window;
    int health = 50;
    int money = 700;
    int current_level_number = 1;
    int current_wave_num = 0;
    Wave current_wave;
    Level current_level;
    std::array<Level, 5> levels;
    sf::Clock wave_timer;
    sf::Clock enemy_timer;
    bool dragging;
    void run();
    void spawn_wave();
    Game(int width, int height, std::string name);

    struct Error {
        std::string name;
        Error(std::string name) : name(name) {};
    };

    void safe_load_texture(sf::Texture& texture, const std::string path) {
        if(!texture.loadFromFile(path)) {
            throw Error("Failed to load the texture stored at " + path);
        }
    }
};



