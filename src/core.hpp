#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <utility>
#include <array>

#include "level.hpp"
#include "turret.hpp"

struct Game {
    std::array<sf::Texture, 5> turret_tex;
    std::array<sf::Texture, 5> enemies_tex;
    std::array<sf::Texture, 5> maps_tex;
    sf::Sprite map_sprite;
    sf::Texture shop_tex;
    sf::Sprite shop_sprite;
    std::vector<Enemy*> enemies;
    std::vector<Turret*> turrets;
    sf::RenderWindow* window;
    int health = 50;
    int money = 1000;
    int current_level_number = 1;
    int current_wave_num = 1;
    Wave current_wave;
    Level current_level;
    std::array<Level, 5> levels;
    sf::Clock wave_timer;
    sf::Clock enemy_timer;
    bool dragging;
    void run();
    void spawn_wave();
    Enemy* spawn_enemy(EnemyType type, sf::Vector2f pos);
    void kill_enemy(Enemy* enemy);
    Turret* spawn_turret(TurretType type, sf::Vector2f pos);
    void kill_turret(Turret* turret);
    Game(int width, int height, std::string name);
    
};