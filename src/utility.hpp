#pragma once 

#include <SFML/Graphics.hpp>

float angle_between(const sf::Vector2f& a, const sf::Vector2f& b);
bool circullar_collide(const sf::Sprite& obj, const sf::Vector2f& point, const float radious);
