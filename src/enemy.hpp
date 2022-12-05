#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

enum class EnemyType {
    Zombie, Alien, Monster
};

struct Enemy : public sf::Sprite {
    int health;
    float speed;
    EnemyType type;
    int path_indx;
    Enemy();
    Enemy(EnemyType type);
};

struct Wave {
    int wave_num;
    std::queue<Enemy> enemies;
};