#include "core.hpp"

void Game::load_sprite(sf::Sprite& obj, std::pair<int, int> index) {
    obj.setTexture(sprite_matrix);
    obj.setTextureRect(sf::IntRect(index.first, index.second, 32 , 32));
}