#pragma once
#include <SFML/Graphics.hpp>
enum class TurretType {
    Rocket, Gun
};
struct Turret : public sf::Sprite {
    TurretType type;
    int cost;
    float radious;
    Turret();
    Turret(TurretType type);
    sf::Clock atack_timer;
    sf::Time attack_cooldown;
};

struct Bullet : public sf::CircleShape {
    float angle;
    float speed;

};