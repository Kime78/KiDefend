#include "utility.hpp"
#include <cmath>

//returns the angle between points a and b in radians, relative to the origin axis
float angle_between(const sf::Vector2f& a, const sf::Vector2f& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return atan2(dy, dx);
}