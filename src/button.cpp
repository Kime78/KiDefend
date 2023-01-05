#include "button.hpp"

sf::RenderWindow* IButton::window = nullptr;

ShopButton::ShopButton(sf::Texture texture, sf::Vector2f position, sf::Vector2i scale) {
    this->scale = scale;
    this->setPosition(position);
    this->setTexture(texture);
}

bool IButton::is_clicked() {
    if(this->getPosition().x > sf::Mouse::getPosition(*window).x && this->getPosition().x < sf::Mouse::getPosition(*window).x + scale.x) {
        if(this->getPosition().y > sf::Mouse::getPosition(*window).y && this->getPosition().y < sf::Mouse::getPosition(*window).y + scale.y) { 
                return true;
            }
        }
    return false;
}

void ShopButton::on_click() {

}