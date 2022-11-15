#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

enum class EnemyType {
    Zombie, Alien, Monster
};
struct Enemy : public sf::Sprite {
    int health;
    EnemyType type;

    Enemy();
};

struct Wave {
    int wave_num;
    std::queue<Enemy> enemies;
};