#pragma once
#include <SFML/Graphics.hpp>
enum class TurretType {
    Rocket, Gun
};
struct Turret : public sf::Sprite {
    TurretType type;
    int cost;
    float radious;
};