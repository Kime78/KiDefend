#include "turret.hpp"


Turret::Turret(TurretType type) {
    switch(type) {
        case TurretType::Gun:
            cost = 500;
            radious = 200;
            attack_cooldown = sf::milliseconds(600);
            break;
        case TurretType::Rocket:
            cost = 1000;
            radious = 150;
            attack_cooldown = sf::milliseconds(500);
            break;
    }

}