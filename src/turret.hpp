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
};

struct Bullet : public sf::CircleShape {
    const float angle;
    const float speed;
};