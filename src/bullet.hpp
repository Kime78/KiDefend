#pragma once

#include "game_object.hpp"

struct Turret;

struct Bullet : public GameObject {
    static std::array<sf::Texture, 10>* textures;
    float angle;
    float speed;
    Turret* origin_turret;
    Bullet(float angle, float speed, Turret* origin_turret, sf::Vector2f pos);

    void update() override;
    void draw() override;
};