#include "enemy.hpp"

Enemy::Enemy() {
    health = 0;
    speed = 1;
    path_indx = 0;
}

Enemy::Enemy(EnemyType type) {
    path_indx = 0;
    switch (type) {
    case EnemyType::Zombie:
        health = 1;
        speed = 0.05;
        break;
    case EnemyType::Alien:
        health = 2;
        speed = 0.1;
        break;
    case EnemyType::Monster:
        health = 4;
        speed = 0.15;
        break;
    default:
        break;
    }
    this->type = type;
}