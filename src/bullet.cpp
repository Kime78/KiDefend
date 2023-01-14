#include <math.h>

#include "bullet.hpp"
#include "enemy.hpp"
#include "utility.hpp"
#include "turret.hpp"

std::array<sf::Texture, 10>* Bullet::textures = nullptr;
int* Bullet::game_money = nullptr;

void Bullet::draw() {
    window->draw(*this);
}

void Bullet::update() {
    float vx = this->speed * cos(this->angle);
    float vy = this->speed * sin(this->angle);
    this->setPosition(this->getPosition().x - vx, this->getPosition().y - vy);
    if(!circular_collide(this->getPosition(), this->origin_turret->getPosition(), this->origin_turret->radius)) {
        objects->remove(this);
    }
    objects->iterate([this](GameObject& obj){
        if (auto enemy = dynamic_cast<Enemy*>(&obj)) {
            if (enemy->getGlobalBounds().contains(getPosition())) {
                objects->remove(this);
                enemy->take_damage();
                (*game_money)++;
                if(enemy->get_health() != 0) {
                    Enemy e(enemy->get_type(), enemy->getPosition());
                    e.setPosition(enemy->getPosition());
                    e.set_path_indx(enemy->get_path_indx());
                    objects->add(std::make_unique<Enemy>(e));
                }
                objects->remove(enemy);
            }
        }
    });  
}

Bullet::Bullet(float angle, float speed, Turret* origin_turret, sf::Vector2f pos) {
    this->angle = angle;
    this->speed = speed;
    this->origin_turret = origin_turret;
    setPosition(pos);
    setTexture((*textures)[0]);
    setOrigin(16, 16);
}