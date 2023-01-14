#include <math.h>

#include "turret.hpp"
#include "enemy.hpp"
#include "utility.hpp"
#include "path.hpp"
#include "bullet.hpp"

std::array<sf::Texture, 10>* Turret::textures = nullptr;


Turret::Turret(TurretType type, sf::Vector2f pos) {
    setPosition(pos);
    setOrigin(16, 16);
    setRotation(0);
    setScale(2, 2);
    this->type = type;
    switch(type) {
        case TurretType::Gun:
            cost = 300;
            radius = 200;
            attack_cooldown = sf::milliseconds(700);
            setTexture((*textures)[0]);
            break;
        case TurretType::MultiBarrelGun:
            cost = 450;
            radius = 150;
            attack_cooldown= sf::milliseconds(850);
            setTexture((*textures)[1]);
            break;
        case TurretType::Rocket:
            cost = 1000;
            radius = 150;
            attack_cooldown = sf::milliseconds(500);
            break;
    }
}

void Turret::draw() {
    window->draw(*this);
}

void Turret::update() {
    Enemy* enemy_short = nullptr;
    float min_dist = INFINITY;
    if(this->type == TurretType::MultiBarrelGun) {
        if(this->atack_timer.getElapsedTime() > this->attack_cooldown) {
            objects->add(std::make_unique<Bullet>(angle_between(this->getPosition(), this->getPosition() + sf::Vector2f(0, 1)), 20, this, this->getPosition()));
            objects->add(std::make_unique<Bullet>(angle_between(this->getPosition(), this->getPosition() + sf::Vector2f(0, -1)), 20, this, this->getPosition()));
            objects->add(std::make_unique<Bullet>(angle_between(this->getPosition(), this->getPosition() + sf::Vector2f(1, 0)), 20, this, this->getPosition()));
            objects->add(std::make_unique<Bullet>(angle_between(this->getPosition(), this->getPosition() + sf::Vector2f(-1, 0)), 20, this, this->getPosition()));
            objects->add(std::make_unique<Bullet>(angle_between(this->getPosition(), this->getPosition() + sf::Vector2f(1, 1)), 20, this, this->getPosition()));
            objects->add(std::make_unique<Bullet>(angle_between(this->getPosition(), this->getPosition() + sf::Vector2f(-1, -1)), 20, this, this->getPosition()));
            objects->add(std::make_unique<Bullet>(angle_between(this->getPosition(), this->getPosition() + sf::Vector2f(-1, 1)), 20, this, this->getPosition()));
            objects->add(std::make_unique<Bullet>(angle_between(this->getPosition(), this->getPosition() + sf::Vector2f(1, -1)), 20, this, this->getPosition()));
            this->atack_timer.restart();
        }
    }
    else {
        objects->iterate([this, &min_dist, &enemy_short](GameObject& obj){
            if(auto enemy = dynamic_cast<Enemy*>(&obj)) {
                if(circular_collide(this->getPosition(), enemy->getPosition(), this->radius)) {
                    auto dist = distance(this->getPosition(), enemy->getPosition());
                    if(dist < min_dist) {
                        min_dist = dist;
                        enemy_short = enemy;
                    }
                }
            }
        });

        if(enemy_short != nullptr) {
            if(circular_collide(this->getPosition(), enemy_short->getPosition(), this->radius)) {
                this->setRotation(angle_between(this->getPosition(), enemy_short->getPosition()) * (180 / PI));
                if(this->atack_timer.getElapsedTime() > this->attack_cooldown) {
                    objects->add(std::make_unique<Bullet>(angle_between(this->getPosition(), enemy_short->getPosition()), 50, this, this->getPosition()));
                    this->atack_timer.restart();
                }
            }
        }
    }
}