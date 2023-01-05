#include "enemy.hpp"

Enemy::Enemy(EnemyType type) {
    path_indx = 0;
    switch (type) {
    case EnemyType::Red:
        health = 1;
        speed = 3;
        break;
    case EnemyType::Blue:
        health = 2;
        speed = 4;
        break;
    case EnemyType::Green:
        health = 3;
        speed = 5;
        break;
    case EnemyType::Yellow:
        health = 4;
        speed = 6;
        break;
    case EnemyType::Pink:
        health = 5;
        speed = 7;
        break;
    case EnemyType::Black:
        health = 6;
        speed = 4;
        break;
    case EnemyType::Lead:
        health = 7;
        speed = 4;
        break;
    default:
        break;
    }
    this->type = type;
    this->setPosition(0, 0);
    this->setOrigin(16, 16);
    this->setRotation(0);
    this->setScale(1.5, 1.5);
}

void Enemy::take_damage() {
    health--;
    switch (type)
    {
    case EnemyType::Red:
        type = EnemyType::Popped;
        break;
    case EnemyType::Blue:
        type = EnemyType::Red;
        break;
    case EnemyType::Green:
        type = EnemyType::Blue;
        break;
    case EnemyType::Yellow:
        type = EnemyType::Green;
        break;
    case EnemyType::Pink:
        type = EnemyType::Yellow;
        break;
    case EnemyType::Black:
        type = EnemyType::Yellow;
        break;
    case EnemyType::Lead:
        type = EnemyType::Black;
        break;
    
    default:
        break;
    }
}

Enemy::Enemy(const Enemy& other) {
    this->path_indx = other.path_indx;
    this->type = other.type;
    this->health = other.health;
    this->speed = other.speed;
    this->setPosition(other.getPosition());
    this->setOrigin(16, 16);
    this->setRotation(0);
    this->setScale(1.5, 1.5);
}