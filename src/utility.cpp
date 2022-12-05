#include "utility.hpp"
#include <cmath>

//returns the angle between points a and b in radians, relative to the origin axis
float angle_between(const sf::Vector2f& a, const sf::Vector2f& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return atan2(dy, dx);
}

bool circullar_collide(const sf::Vector2f& obj_pos, const sf::Vector2f& point, const float radious) {
    if(obj_pos.x > point.x - radious && obj_pos.x < point.x + radious) {
            if(obj_pos.y > point.y - radious && obj_pos.y < point.y + radious) { // to be reduced in a func {
                return true;
           }
        }
    return false;
}