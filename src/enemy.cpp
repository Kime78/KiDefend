#include "enemy.hpp"
#include "level.hpp"
#include "utility.hpp"

Level* Enemy::current_level = nullptr;
std::array<sf::Texture, 10>* Enemy::textures = nullptr;
int* Enemy::game_health = nullptr;

Enemy::Enemy(EnemyType type, sf::Vector2f pos) {
    path_indx = 0;
    this->setPosition(pos);
    switch (type) {
    case EnemyType::Red:
        health = 1;
        speed = 3;
        setTexture((*textures)[0]);
        break;
    case EnemyType::Blue:
        health = 2;
        speed = 4;
        setTexture((*textures)[1]);
        break;
    case EnemyType::Green:
        health = 3;
        speed = 5;
        setTexture((*textures)[2]);
        break;
    case EnemyType::Yellow:
        health = 4;
        speed = 6;
        setTexture((*textures)[3]);
        break;
    case EnemyType::Pink:
        health = 5;
        speed = 7;
        setTexture((*textures)[4]);
        break;
    case EnemyType::Black:
        health = 6;
        speed = 4;
        setTexture((*textures)[5]);
        break;
    case EnemyType::Lead:
        health = 7;
        speed = 4;
        setTexture((*textures)[6]);
        break;
    default:
        break;
    }
    this->type = type;
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
    this->setTexture(*other.getTexture());
    this->setPosition(other.getPosition());
    this->setOrigin(16, 16);
    this->setRotation(0);
    this->setScale(1.5, 1.5);
}

void Enemy::draw() {
    if(this->type != EnemyType::Popped)
        window->draw(*this);
}

void Enemy::update() {
    current_level->path->move_in_path(*this);
    if(rectular_collide(this->getPosition(), current_level->path->path.back(), sf::Vector2f(30, 30))) {
        objects->remove(this);
        *game_health -= this->get_health();
    }
}