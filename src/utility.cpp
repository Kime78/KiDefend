#include "utility.hpp"
#include <cmath>

//returns the angle between points a and b in radians, relative to the origin axis
float angle_between(const sf::Vector2f& a, const sf::Vector2f& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return atan2(dy, dx);
}

bool rectular_collide(const sf::Vector2f& obj_pos, const sf::Vector2f& point, const sf::Vector2f& size) {
    if(obj_pos.x > point.x - size.x && obj_pos.x < point.x + size.x) {
            if(obj_pos.y > point.y - size.y && obj_pos.y < point.y + size.y) { 
                return true;
           }
        }
    return false;
}

float distance(const sf::Vector2f a, const sf::Vector2f b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

bool circular_collide(const sf::Vector2f obj_pos, const sf::Vector2f point, const float radious) {
    return sqrt(pow(obj_pos.x - point.x, 2) - pow(obj_pos.y - point.y, 2)) < radious;
}