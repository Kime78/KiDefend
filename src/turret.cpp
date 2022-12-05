#include "turret.hpp"

Turret::Turret() {
    cost = 500;
    radious = 100;
}

Turret::Turret(TurretType type) {
    switch(type) {
        case TurretType::Gun:
            cost = 500;
            radious = 100;
            break;
        case TurretType::Rocket:
            cost = 1000;
            radious = 80;
            break;
    }
}