#pragma once
#include <SFML/Graphics.hpp>
#include "game_object.hpp"
enum class TurretType {
    Rocket, Gun, MultiBarrelGun,
};
struct Turret : public GameObject {
    static std::array<sf::Texture, 10>* textures;
    TurretType type;
    int cost;
    float radius;
    Turret();
    Turret(TurretType type, sf::Vector2f pos);
    sf::Clock atack_timer;
    sf::Time attack_cooldown;

    void update() override;
    void draw() override;
};

