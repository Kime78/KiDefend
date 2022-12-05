#pragma once 

#include <SFML/Graphics.hpp>

float angle_between(const sf::Vector2f& a, const sf::Vector2f& b);
bool rectular_collide(const sf::Vector2f& obj_pos, const sf::Vector2f& point, const sf::Vector2f& size);
